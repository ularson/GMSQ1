/*
  ==============================================================================

    Env1GUI.h
    Created: 12 May 2024 11:38:41pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct Env1GUI : juce::Component
{
    Env1GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    juce::String label;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> env1AttackSlider, env1DecaySlider, env1SustainSlider, env1ReleaseSlider, env1KeySlider, env1VelSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> env1AttackSliderAttachment, env1DecaySliderAttachment, env1SustainSliderAttachment, env1ReleaseSliderAttachment, env1KeySliderAttachment, env1VelSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> env1EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> env1EnabledButtonAttachment;
};
