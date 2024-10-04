/*
  ==============================================================================

    Master.h
    Created: 16 Apr 2024 12:31:03am
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../GUI/Utilities.h"

struct Master : juce::dsp::Gain<float>
{
    void setGain(const float level);
    void setNrOfVoices(const float voices);
    void setPitchBend(const float bendRange);
    float getPitchBend();
    void setParams(const float gain, const int voices, const int pitchBend, const bool enabled);
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void processNextBlock(juce::AudioBuffer<float>& buffer);
    int getNrOfvoices();
    void setNrOfvoices(int voices);
private:
    int nrOfvoices;
    int pitchBend;
    
    void disableMaster ();
};
