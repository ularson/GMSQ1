/*
  ==============================================================================

    SynthVoice.h
    Created: 12 Mar 2022 7:57:25pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "DSP/Osc.h"
#include "DSP/Filter.h"
#include "DSP/Env.h"
#include "DSP/LFO.h"
#include "DSP/Master.h"
#include "DSP/ModMatrix.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    
    void startNote (int midiNoteNumber, float vel, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void setPitchBend(int pitchWheelPos);
    
    float pitchBendCents();
    
    double noteHz(int midiNoteNumber, double centsOffset);
    
    void updateOsc1(const int wave, const float semitones, const float cents, const float level, const float PW, const bool enabled, const float sync, const float FM);
    void updateOsc2(const int wave, const float semitones, const float cents, const float level, const float PW, const bool enabled, const float sync, const float FM);
    void updateOsc3(const int wave, const float semitones, const float cents, const float level, const float PW, const bool enabled, const float sync, const float FM);
    
    void updateFilter(const int mode, const float cutoff, const float resonance, const float vel, const float key, const bool enabled, const float env);
    
    void updateLfo(LFO& lfo, const int source, const int destination, const int wave, const float rate, const float gain, const bool reset, const bool enabled, const float cutoff = 1.0f);
    
    void updateMod(const int source, const int destination, const int value, const float cutoff, const float pulseWidth, const float vel, const float modWheel);
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    Osc& getOsc1() { return osc1; }
    Osc& getOsc2() { return osc2; }
    Osc& getOsc3() { return osc3; }
    Filter& getFilter() { return filter; }
    Env& getEnv1() { return env1; }
    Env& getEnv2() { return env2; }
    Env& getEnv3() { return env3; }
    LFO& getLfo1() { return lfo1; }
    LFO& getLfo2() { return lfo2; }
    ModMatrix& getModMatrix() { return modMatrix; }
    Master& getMaster() { return master; }
    
private:
    Osc osc1;
    Osc osc2;
    Osc osc3;
    Filter filter;
    Env env1;
    Env env2;
    Env env3;
    LFO lfo1;
    LFO lfo2;
    Master master;
    ModMatrix modMatrix;
    juce::AudioBuffer<float> synthBuffer;
    
    int noteNumber;
    double velocity, frequency;
    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;
    int modWheel = 0;
};
