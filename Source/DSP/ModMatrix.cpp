/*
  ==============================================================================

    ModMatrix.cpp
    Created: 18 Apr 2024 11:37:08pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "ModMatrix.h"


void ModMatrix::setOsc1PitchModParams(float osc1PitchEnv1, float osc1PitchEnv2, float osc1PitchLfo1, float osc1PitchLfo2, float osc1PitchVel, float osc1PitchMod)
{
    if(enabled) {
        modMatrix[Source::Env1][Destination::Osc1Pitch] = osc1PitchEnv1;
        modMatrix[Source::Env2][Destination::Osc1Pitch] = osc1PitchEnv2;
        modMatrix[Source::Lfo1][Destination::Osc1Pitch] = osc1PitchLfo1;
        modMatrix[Source::Lfo2][Destination::Osc1Pitch] = osc1PitchLfo2;
        modMatrix[Source::Vel][Destination::Osc1Pitch] = osc1PitchVel;
        modMatrix[Source::ModWheel][Destination::Osc1Pitch] = osc1PitchMod;
    } else {
        disableMod();
    }
}

void ModMatrix::setOsc2PitchModParams(float osc2PitchEnv1, float osc2PitchEnv2, float osc2PitchLfo1, float osc2PitchLfo2, float osc2PitchVel, float osc2PitchMod)
{
    if(enabled) {
        modMatrix[Source::Env1][Destination::Osc2Pitch] = osc2PitchEnv1;
        modMatrix[Source::Env2][Destination::Osc2Pitch] = osc2PitchEnv2;
        modMatrix[Source::Lfo1][Destination::Osc2Pitch] = osc2PitchLfo1;
        modMatrix[Source::Lfo2][Destination::Osc2Pitch] = osc2PitchLfo2;
        modMatrix[Source::Vel][Destination::Osc2Pitch] = osc2PitchVel;
        modMatrix[Source::ModWheel][Destination::Osc2Pitch] = osc2PitchMod;
    } else {
        disableMod();
    }
}

void ModMatrix::setOsc3PitchModParams(float osc3PitchEnv1, float osc3PitchEnv2, float osc3PitchLfo1, float osc3PitchLfo2, float osc3PitchVel, float osc3PitchMod)
{
    if(enabled) {
        modMatrix[Source::Env1][Destination::Osc3Pitch] = osc3PitchEnv1;
        modMatrix[Source::Env2][Destination::Osc3Pitch] = osc3PitchEnv2;
        modMatrix[Source::Lfo1][Destination::Osc3Pitch] = osc3PitchLfo1;
        modMatrix[Source::Lfo2][Destination::Osc3Pitch] = osc3PitchLfo2;
        modMatrix[Source::Vel][Destination::Osc3Pitch] = osc3PitchVel;
        modMatrix[Source::ModWheel][Destination::Osc3Pitch] = osc3PitchMod;
    } else {
        disableMod();
    }
}

void ModMatrix::setCutoffModParams(float cutoffEnv1, float cutoffEnv2, float cutoffLfo1, float cutoffLfo2, float cutoffVel, float cutoffMod)
{
    if(enabled) {
        modMatrix[Source::Env1][Destination::FilterCutoff] = cutoffEnv1;
        modMatrix[Source::Env2][Destination::FilterCutoff] = cutoffEnv2;
        modMatrix[Source::Lfo1][Destination::FilterCutoff] = cutoffLfo1;
        modMatrix[Source::Lfo2][Destination::FilterCutoff] = cutoffLfo2;
        modMatrix[Source::Vel][Destination::FilterCutoff] = cutoffVel;
        modMatrix[Source::ModWheel][Destination::FilterCutoff] = cutoffMod;
    } else {
        disableMod();
    }
}

void ModMatrix::setPWModParams(float pwEnv1, float pwEnv2, float pwLfo1, float pwLfo2, float pwVel, float pwMod)
{
    if(enabled) {
        modMatrix[Source::Env1][Destination::PulseWidth] = pwEnv1;
        modMatrix[Source::Env2][Destination::PulseWidth] = pwEnv2;
        modMatrix[Source::Lfo1][Destination::PulseWidth] = pwLfo1;
        modMatrix[Source::Lfo2][Destination::PulseWidth] = pwLfo2;
        modMatrix[Source::Vel][Destination::PulseWidth] = pwVel;
        modMatrix[Source::ModWheel][Destination::PulseWidth] = pwMod;
    } else {
        disableMod();
    }
}

bool ModMatrix::getEnabled() {
    return enabled;
}

void ModMatrix::setEnabled(bool modEnabled) {
    enabled = modEnabled;
}

void ModMatrix::disableMod() {
    for (int s = 0; s < 6; ++s) {
        for (int d = 0; d < 5; ++d) {
            modMatrix[s][d] = 0;
        }
    }
    
    enabled = false;
}
