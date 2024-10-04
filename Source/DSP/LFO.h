/*
  ==============================================================================

    LFO.h
    Created: 14 Apr 2024 11:46:59pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LFO : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void setWave (const int wave);
    void setRate (const float rate);
    void setLevel (const float level);
    void setReset (const bool reset);
    void renderNextBlock (juce::dsp::AudioBlock<float>& audioBlock);
    float processNextSample (float input);
    void setParams (const int source, const int destination, const int wave, const float rate, const float level, const bool reset, const bool enabled);
    void resetAll();
    bool enabled { true };
    
    enum Sources {
        None,
        Modulation
    };
    
    enum Destinations {
        Pitch,
        Cutoff,
        PW
    };
    
private:
    juce::dsp::Gain<float> gain;
    void disableLfo ();
};
