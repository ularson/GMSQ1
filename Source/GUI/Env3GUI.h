/*
  ==============================================================================

    Env3GUI.h
    Created: 13 May 2024 12:11:35am
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct Env3GUI : juce::Component
{
    Env3GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    juce::String label;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> env3AttackSlider, env3DecaySlider, env3SustainSlider, env3ReleaseSlider, env3KeySlider, env3VelSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> env3AttackSliderAttachment, env3DecaySliderAttachment, env3SustainSliderAttachment, env3ReleaseSliderAttachment, env3KeySliderAttachment, env3VelSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> env3EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> env3EnabledButtonAttachment;
};
