/*
  ==============================================================================

    Oscillator.h
    Created: 1 Jan 2021 2:49:35pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct Osc : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void setWave (const int wave, const float duty);
    void setOscPitch (const int semitones, const float cents);
    void setFreq (const int midiNoteNumber);
    void setLevel (const float level);
    void renderNextBlock (juce::dsp::AudioBlock<float>& audioBlock);
    float processNextSample (float input);
    void setParams (const int wave, const int semi, const int cents, const float level, const float pw, const bool enabled, const float sync, const float fm );
    void setPulseWidth(const float duty);
    float getPulseWidth();
    void resetAll();
    bool enabled { true };
private:
    juce::dsp::Gain<float> gain;
    int lastPitch { 0 };
    int lastMidiNote { 0 };
    float pulseWidth;
    void disableOsc ();
};
