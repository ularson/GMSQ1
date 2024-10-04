/*
  ==============================================================================

    Filter.h
    Created: 13 Apr 2024 11:46:38pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../GUI/Utilities.h"

class Filter : public juce::dsp::LadderFilter<float>
{
public:
    Filter();
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void setParams (const int filterMode, const float filterCutoff, const float filterResonance, const int filterVel, const float filterKey, const bool enabled, const float filterEnv = 1.0f);
    void processNextBlock (juce::AudioBuffer<float>& buffer);
    float processNextSample (int channel, float inputValue);
    void resetAll();
    bool enabled { true };
private:
    void selectFilterMode (const int mode);
    void disableFilter ();
    float setEnv(const float filterCutoff, const float filterEnv);
};
