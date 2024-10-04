/*
  ==============================================================================

    LFO.cpp
    Created: 14 Apr 2024 11:46:59pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "LFO.h"
#include "../GUI/Utilities.h"

void LFO::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    prepare (spec);
    gain.prepare (spec);
}

void LFO::setWave (const int wave)
{
    switch (wave)
    {
        case Const::SINE_WAVE:
            initialise ([](float x) { return std::sin (x); }, 128);
            break;
            
        case Const::SAW_WAVE:
            initialise ([] (float x) { return juce::jmap (x,
                                      float (-juce::MathConstants<double>::pi),
                                      float (juce::MathConstants<double>::pi),
                                      float (-1),
                                      float (1));
                                    }, 2);
            break;
          
        case Const::SQUARE_WAVE:
            initialise ([] (float x) { return x < 0.0f ? -1.0f : 1.0f; });
            break;
            
        case Const::TRIANGLE_WAVE:
            initialise([](float x) {
                    return (x < 0) ?
                        juce::jmap(x,
                            float(-juce::MathConstants<double>::pi),
                            float(0),
                            float(-1),
                            float(1)) :
                        juce::jmap(x,
                            float(0),
                            float(juce::MathConstants<double>::pi),
                            float(1),
                            float(-1));
                        }, 128);
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void LFO::setLevel(const float level)
{
    gain.setGainLinear (level);
}

void LFO::setRate (const float rate)
{
    setFrequency (rate);
}

//void LFO::setReset (const bool reset)
//{
//    if(reset)
//    {
//        setFrequency(0);
//    }
//}

void LFO::setParams (const int source, const int destination, const int wave, const float rate, const float level, const bool reset, const bool enabled)
{
    if(enabled) {
        setWave (wave);
        setLevel (level);
        setRate (rate);
//        setReset (reset);
    } else {
        disableLfo();
    }
}

void LFO::renderNextBlock (juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert (audioBlock.getNumSamples() > 0);
    process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
}

float LFO::processNextSample (float input)
{
    return gain.processSample (processSample (input));
}

void LFO::resetAll()
{
    reset();
    gain.reset();
}

void LFO::disableLfo ()
{
    initialise ([] (float x) { return 0; });
    setRate(0);
    setLevel(0);
}
