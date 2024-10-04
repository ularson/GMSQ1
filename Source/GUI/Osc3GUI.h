/*
  ==============================================================================

    Osc3GUI.h
    Created: 9 May 2024 11:19:05pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "RotarySliderWithTextbox.h"

struct Osc3GUI : juce::Component
{
    Osc3GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> osc3WaveSlider, osc3LevelSlider, osc3SemitonesSlider, osc3CentsSlider, osc3PWSlider, osc3FMSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> osc3WaveSliderAttachment, osc3LevelSliderAttachment, osc3SemitonesSliderAttachment, osc3CentsSliderAttachment, osc3PWSliderAttachment, osc3FMSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> osc3EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> osc3EnabledEnabledAttachment;
};
