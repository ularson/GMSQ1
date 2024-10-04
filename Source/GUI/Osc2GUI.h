/*
  ==============================================================================

    Osc2GUI.h
    Created: 9 May 2024 11:18:50pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct Osc2GUI : juce::Component
{
    Osc2GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> osc2WaveSlider, osc2LevelSlider, osc2SemitonesSlider, osc2CentsSlider, osc2PWSlider, osc2FMSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> osc2WaveSliderAttachment, osc2LevelSliderAttachment, osc2SemitonesSliderAttachment, osc2CentsSliderAttachment, osc2PWSliderAttachment, osc2FMSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> osc2EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> osc2EnabledButtonAttachment;

};
