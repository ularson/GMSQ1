/*
  ==============================================================================

    Filter.cpp
    Created: 13 Apr 2024 11:46:38pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Filter.h"

Filter::Filter()
{
    setMode (juce::dsp::LadderFilterMode::LPF24);
}

void Filter::setParams (const int filterMode, const float filterCutoff, const float filterResonance, const int filterVel, const float filterKey, const bool enabled, const float filterEnv)
{
    if(enabled) {
        selectFilterMode (filterMode);
        auto modFreq = setEnv(filterCutoff, filterEnv);
        setCutoffFrequencyHz (modFreq);
        setResonance (filterResonance);
            } else {
        disableFilter();
    }
}

void Filter::disableFilter ()
{
    setMode(juce::dsp::LadderFilterMode::LPF24);
    setCutoffFrequencyHz(Const::MAX_FREQUENCY);
    setResonance(0);
}

float Filter::setEnv(const float filterCutoff, const float filterEnv)
{
    float modFreq = filterEnv > 0 ? filterCutoff * filterEnv : filterCutoff;
    modFreq = juce::jlimit(20.f, 20000.f, modFreq);
    return modFreq;
}

void Filter::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    prepare (spec);
}


void Filter::selectFilterMode (const int mode)
{
    switch (mode)
    {
        case Const::LPF24:
            setMode (juce::dsp::LadderFilterMode::LPF24);
            break;
            
        case Const::LPF12:
            setMode (juce::dsp::LadderFilterMode::LPF12);
            break;
            
        case Const::BPF24:
            setMode (juce::dsp::LadderFilterMode::BPF24);
            break;
            
        case Const::BPF12:
            setMode (juce::dsp::LadderFilterMode::BPF12);
            break;
            
        case Const::HPF24:
            setMode (juce::dsp::LadderFilterMode::HPF24);
            break;
            
        case Const::HPF12:
            setMode (juce::dsp::LadderFilterMode::HPF12);
            break;
            
        default:
            setMode (juce::dsp::LadderFilterMode::LPF24);
            break;
    }
}

void Filter::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block { buffer };
    process (juce::dsp::ProcessContextReplacing<float>(block));
}

float Filter::processNextSample (int channel, float inputValue)
{
    return processSample (channel, inputValue);
}

void Filter::resetAll()
{
    reset();
}
