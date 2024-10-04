/*
  ==============================================================================

    ModMatrix.h
    Created: 18 Apr 2024 11:37:08pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Osc.h"
#include "Env.h"
#include "LFO.h"

struct ModMatrix {
    
    void setOsc1PitchModParams(float osc1PitchEnv1, float osc1PitchEnv2, float osc1PitchLfo1, float osc1PitchLfo2, float osc1PitchVel, float osc1PitchMod);
    
    void setOsc2PitchModParams(float osc2PitchEnv1, float osc2PitchEnv2, float osc2PitchLfo1, float osc2PitchLfo2, float osc2PitchVel, float osc2PitchMod);
    
    void setOsc3PitchModParams(float osc3PitchEnv1, float osc3PitchEnv2, float osc3PitchLfo1, float osc3PitchLfo2, float osc3PitchVel, float osc3PitchMod);
    
    void setCutoffModParams(float cutoffEnv1, float cutoffEnv2, float cutoffLfo1, float cutoffLfo2, float cutoffVel, float cutoffMod);
    
    void setPWModParams(float pwEnv1, float pwEnv2, float pwLfo1, float pwLfo2, float pwVel, float pwMod);
    
    bool getEnabled();
    
    void setEnabled(bool enabled);
    
    enum Source
    {
        Env1,
        Env2,
        Lfo1,
        Lfo2,
        Vel,
        ModWheel
    };
    
    enum Destination
    {
        Osc1Pitch,
        Osc2Pitch,
        Osc3Pitch,
        FilterCutoff,
        PulseWidth
    };
    
private:
    int modMatrix [6][5] = {0};
    bool enabled { true };
    
    Osc osc1, osc2, osc3;
    Env env1, env2, env3;
    LFO lfo1, lfo2;
    
    void disableMod ();
};
