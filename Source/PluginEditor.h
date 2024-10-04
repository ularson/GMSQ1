/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/LookAndFeel.h"
#include "GUI/Osc1GUI.h"
#include "GUI/Osc2GUI.h"
#include "GUI/Osc3GUI.h"
#include "GUI/Env1GUI.h"
#include "GUI/Env2GUI.h"
#include "GUI/Env3GUI.h"
#include "GUI/LFO1GUI.h"
#include "GUI/LFO2GUI.h"
#include "GUI/FilterGUI.h"
#include "GUI/ModMatrixGUI.h"
#include "GUI/MasterGUI.h"
#include "GUI/Utilities.h"

//==============================================================================
/**
*/
class GMSQ1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GMSQ1AudioProcessorEditor (GMSQ1AudioProcessor&);
    ~GMSQ1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LookAndFeel lnf;
    GMSQ1AudioProcessor& audioProcessor;
    Osc1GUI osc1GUI { audioProcessor.apvts };
    Osc2GUI osc2GUI { audioProcessor.apvts };
    Osc3GUI osc3GUI { audioProcessor.apvts };
    FilterGUI filterGUI { audioProcessor.apvts };
    Env1GUI env1GUI { audioProcessor.apvts };
    Env2GUI env2GUI { audioProcessor.apvts };
    Env3GUI env3GUI { audioProcessor.apvts };
    LFO1GUI lfo1GUI { audioProcessor.apvts };
    LFO2GUI lfo2GUI { audioProcessor.apvts };
    ModMatrixGUI modMatrixGUI { audioProcessor.apvts };
    MasterGUI masterGUI { audioProcessor.apvts };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GMSQ1AudioProcessorEditor)
};
