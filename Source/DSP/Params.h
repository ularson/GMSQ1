/*
  ==============================================================================

    Params.h
    Created: 10 Apr 2024 10:43:39pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Params
{
enum Names
{
    Osc1_Wave,
    Osc1_Semitones,
    Osc1_Cents,
    Osc1_Level,
    Osc1_PW,
    Osc1_Sync,
    Osc1_Enabled,
    
    Osc2_Wave,
    Osc2_Semitones,
    Osc2_Cents,
    Osc2_Level,
    Osc2_PW,
    Osc2_FM,
    Osc2_Enabled,
    
    Osc3_Wave,
    Osc3_Semitones,
    Osc3_Cents,
    Osc3_Level,
    Osc3_PW,
    Osc3_Enabled,
    
    Filter_Mode,
    Filter_Cutoff,
    Filter_Res,
    Filter_Vel,
    Filter_Env,
    Filter_Key,
    Filter_Enabled,
    
    ENV1_Attack,
    ENV1_Decay,
    ENV1_Sustain,
    ENV1_Release,
    ENV1_Key,
    ENV1_Vel,
    ENV1_Enabled,
    
    ENV2_Attack,
    ENV2_Decay,
    ENV2_Sustain,
    ENV2_Release,
    ENV2_Key,
    ENV2_Vel,
    ENV2_Enabled,
    
    ENV3_Attack,
    ENV3_Decay,
    ENV3_Sustain,
    ENV3_Release,
    ENV3_Key,
    ENV3_Vel,
    ENV3_Enabled,
    
    LFO1_Source,
    LFO1_Dest,
    LFO1_Wave,
    LFO1_Rate,
    LFO1_Gain,
    LFO1_Reset,
    LFO1_Enabled,
    
    LFO2_Source,
    LFO2_Dest,
    LFO2_Wave,
    LFO2_Rate,
    LFO2_Gain,
    LFO2_Reset,
    LFO2_Enabled,
    
    Osc1_Pitch_Env1,
    Osc1_Pitch_Env2,
    Osc1_Pitch_Lfo1,
    Osc1_Pitch_Lfo2,
    Osc1_Pitch_Vel,
    Osc1_Pitch_Mod,
    
    Osc2_Pitch_Env1,
    Osc2_Pitch_Env2,
    Osc2_Pitch_Lfo1,
    Osc2_Pitch_Lfo2,
    Osc2_Pitch_Vel,
    Osc2_Pitch_Mod,
    
    Osc3_Pitch_Env1,
    Osc3_Pitch_Env2,
    Osc3_Pitch_Lfo1,
    Osc3_Pitch_Lfo2,
    Osc3_Pitch_Vel,
    Osc3_Pitch_Mod,
    
    Cutoff_Env1,
    Cutoff_Env2,
    Cutoff_Lfo1,
    Cutoff_Lfo2,
    Cutoff_Vel,
    Cutoff_Mod,
    
    PW_Env1,
    PW_Env2,
    PW_Lfo1,
    PW_Lfo2,
    PW_Vel,
    PW_Mod,
    
    Mod_Enabled,
    
    Master_Gain,
    Nr_Of_Voices,
    Pitch_Bend,
    Master_Enabled,
};

inline const std::map<Names, juce::String>& GetParams()
{
    static std::map<Names, juce::String> params =
    {
        {Osc1_Wave, "Osc1 Wave"},
        {Osc1_Semitones, "Osc1 Semi"},
        {Osc1_Cents, "Osc1 Cents"},
        {Osc1_Level, "Osc1 Level"},
        {Osc1_PW, "Osc1 PW"},
        {Osc1_Sync, "Osc1 Sync"},
        {Osc1_Enabled, "Osc1 Enabled"},
        
        {Osc2_Wave, "Osc2 Wave"},
        {Osc2_Semitones, "Osc2 Semi"},
        {Osc2_Cents, "Osc2 Cents"},
        {Osc2_Level, "Osc2 Level"},
        {Osc2_PW, "Osc2 PW"},
        {Osc2_FM, "Osc2 FM"},
        {Osc2_Enabled, "Osc2 Enabled"},
        
        {Osc3_Wave, "Osc3 Wave"},
        {Osc3_Semitones, "Osc3 Semi"},
        {Osc3_Cents, "Osc3 Cents"},
        {Osc3_Level, "Osc3 Level"},
        {Osc3_PW, "Osc3 PW"},
        {Osc3_Enabled, "Osc3 Enabled"},
        
        {Filter_Mode, "Filter Mode"},
        {Filter_Cutoff, "Filter Cutoff"},
        {Filter_Res, "Filter Res"},
        {Filter_Vel, "Filter Vel"},
        {Filter_Env, "Filter Env"},
        {Filter_Key, "Filter Key"},
        {Filter_Enabled, "Filter Enabled"},
        
        {ENV1_Attack, "ENV1 Attack"},
        {ENV1_Decay, "ENV1 Decay"},
        {ENV1_Sustain, "ENV1 Sustain"},
        {ENV1_Release, "ENV1 Release"},
        {ENV1_Key, "ENV1 Key"},
        {ENV1_Vel, "ENV1 Vel"},
        {ENV1_Enabled, "ENV1 Enabled"},
        
        {ENV2_Attack, "ENV2 Attack"},
        {ENV2_Decay, "ENV2 Decay"},
        {ENV2_Sustain, "ENV2 Sustain"},
        {ENV2_Release, "ENV2 Release"},
        {ENV2_Key, "ENV2 Key"},
        {ENV2_Vel, "ENV2 Vel"},
        {ENV2_Enabled, "ENV2 Enabled"},
        
        {ENV3_Attack, "ENV3 Attack"},
        {ENV3_Decay, "ENV3 Decay"},
        {ENV3_Sustain, "ENV3 Sustain"},
        {ENV3_Release, "ENV3 Release"},
        {ENV3_Key, "ENV3 Key"},
        {ENV3_Vel, "ENV3 Vel"},
        {ENV3_Enabled, "ENV3 Enabled"},
        
        {LFO1_Source, "LFO1 Source"},
        {LFO1_Dest, "LFO1 Dest"},
        {LFO1_Wave, "LFO1 Wave"},
        {LFO1_Gain, "LFO1 Gain"},
        {LFO1_Rate, "LFO1 Rate"},
        {LFO1_Reset, "LFO1 Reset"},
        {LFO1_Enabled, "LFO1 Enabled"},
        
        {LFO2_Source, "LFO2 Source"},
        {LFO2_Dest, "LFO2 Dest"},
        {LFO2_Wave, "LFO2 Wave"},
        {LFO2_Gain, "LFO2 Gain"},
        {LFO2_Rate, "LFO2 Rate"},
        {LFO2_Reset, "LFO2 Reset"},
        {LFO2_Enabled, "LFO2 Enabled"},
        
        {Osc1_Pitch_Env1, "Osc1 Pitch Env1"},
        {Osc1_Pitch_Env2, "Osc1 Pitch Env2"},
        {Osc1_Pitch_Lfo1, "Osc1 Pitch Lfo1"},
        {Osc1_Pitch_Lfo2, "Osc1 Pitch Lfo2"},
        {Osc1_Pitch_Vel, "Osc1 Pitch Vel"},
        {Osc1_Pitch_Mod, "Osc1 Pitch Mod"},
        
        {Osc2_Pitch_Env1, "Osc2 Pitch Env1"},
        {Osc2_Pitch_Env2, "Osc2 Pitch Env2"},
        {Osc2_Pitch_Lfo1, "Osc2 Pitch Lfo1"},
        {Osc2_Pitch_Lfo2, "Osc2 Pitch Lfo2"},
        {Osc2_Pitch_Vel, "Osc2 Pitch Vel"},
        {Osc2_Pitch_Mod, "Osc2 Pitch Mod"},
        
        {Osc3_Pitch_Env1, "Osc3 Pitch Env1"},
        {Osc3_Pitch_Env2, "Osc3 Pitch Env2"},
        {Osc3_Pitch_Lfo1, "Osc3 Pitch Lfo1"},
        {Osc3_Pitch_Lfo2, "Osc3 Pitch Lfo2"},
        {Osc3_Pitch_Vel, "Osc3 Pitch Vel"},
        {Osc3_Pitch_Mod, "Osc3 Pitch Mod"},
        
        {Cutoff_Env1, "Cutoff Env1"},
        {Cutoff_Env2, "Cutoff Env2"},
        {Cutoff_Lfo1, "Cutoff Lfo1"},
        {Cutoff_Lfo2, "Cutoff Lfo2"},
        {Cutoff_Vel, "Cutoff Vel"},
        {Cutoff_Mod, "Cutoff Mod"},
        
        {PW_Env1, "PW Env1"},
        {PW_Env2, "PW Env2"},
        {PW_Lfo1, "PW Lfo1"},
        {PW_Lfo2, "PW Lfo2"},
        {PW_Vel, "PW Vel"},
        {PW_Mod, "PW Mod"},
        
        {Mod_Enabled, "Mod Enabled"},
        
        {Master_Gain, "Master Gain"},
        {Nr_Of_Voices, "Number of voices"},
        {Pitch_Bend, "Pitch Bend"},
        {Master_Enabled, "Master Enabled"}
    };
    
    return params;
}
}
