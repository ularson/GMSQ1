/*
  ==============================================================================

    MasterGUI.h
    Created: 20 May 2024 11:33:10pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct MasterGUI : juce::Component
{
    MasterGUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> gainSlider, pitchBendSlider, nrOfVoicesSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> gainSliderAttachment, pitchBendSliderAttachment, nrOfVoicesSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> masterEnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> masterEnabledButtonAttachment;
};
