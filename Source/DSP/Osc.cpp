/*
  ==============================================================================

    Oscillator.cpp
    Created: 1 Jan 2021 2:49:35pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Osc.h"
#include "../GUI/Utilities.h"

void Osc::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    prepare (spec);
    gain.prepare (spec);
}

void Osc::setWave (const int wave, const float duty)
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
        
        case Const::PULSE_WAVE:
            initialise ([duty] (float x) { return x < duty ? -1.0f : 1.0f; });
            break;
            
 
        case Const::NOISE_WAVE:
            initialise ([] (float x) { return juce::Random::getSystemRandom().nextFloat() * 2 - 1; });
            break;

            
        default:
            jassertfalse;
            break;
    }
}

// NOT WORKING!!
void Osc::setLevel(const float level)
{
    //DBG( "level: " << level );
    gain.setGainLinear (level);
}

// NOT WORKING!!
void Osc::setOscPitch (const int semitones, const float cents)
{
    double root = std::exp (std::log(2) / 1200);
    double cent = pow(root, cents);
    //DBG( "lastPitch: " << lastPitch << ", semitones: " << semitones << ", cents: " << cents << ", cent: " << cent );
    lastPitch = semitones * cent;
    setFrequency (juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch)));

}

void Osc::setFreq (const int midiNoteNumber)
{
    setFrequency (juce::MidiMessage::getMidiNoteInHertz ((midiNoteNumber + lastPitch)));
    lastMidiNote = midiNoteNumber;
}

void Osc::setPulseWidth(const float duty)
{
    initialise ([duty] (float x) { return x < duty ? -1.0f : 1.0f; });
    pulseWidth = duty;
}

float Osc::getPulseWidth()
{
    return pulseWidth;
}

void Osc::disableOsc ()
{
    initialise ([] (float x) { return 0; });
}

void Osc::setParams (const int wave, const int semi, const int cents, const float level, const float pw, const bool enabled, const float sync, const float fm)
{
    if(enabled){
        setWave (wave, pw);
        setOscPitch (semi, cents);
        setLevel (level);
        setPulseWidth(pw);
    } else {
        disableOsc();
    }
}

void Osc::renderNextBlock (juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert (audioBlock.getNumSamples() > 0);
    process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
}

float Osc::processNextSample (float input)
{
    return gain.processSample (processSample (input));
}

void Osc::resetAll()
{
    reset();
    gain.reset();
}
