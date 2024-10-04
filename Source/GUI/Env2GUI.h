/*
  ==============================================================================

    Env2GUI.h
    Created: 13 May 2024 12:11:19am
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct Env2GUI : juce::Component
{
    Env2GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    juce::String label;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> env2AttackSlider, env2DecaySlider, env2SustainSlider, env2ReleaseSlider, env2KeySlider, env2VelSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> env2AttackSliderAttachment, env2DecaySliderAttachment, env2SustainSliderAttachment, env2ReleaseSliderAttachment, env2KeySliderAttachment, env2VelSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> env2EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> env2EnabledButtonAttachment;
};
