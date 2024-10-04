/*
  ==============================================================================

    FilterGUI.h
    Created: 9 May 2024 10:25:58pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RotarySliderWithTextbox.h"
#include "LookAndFeel.h"
#include "Utilities.h"
#include "../DSP/Params.h"


struct FilterGUI : juce::Component
{
    FilterGUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> filterModeSlider, filterCutoffSlider, filterResonanceSlider, filterVelSlider, filterEnvSlider, filterKeySlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> filterModeSliderAttachment, filterCutoffSliderAttachment, filterResonanceSliderAttachment, filterVelSliderAttachment, filterEnvSliderAttachment, filterKeySliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> filterEnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> filterEnabledButtonAttachment;
};
