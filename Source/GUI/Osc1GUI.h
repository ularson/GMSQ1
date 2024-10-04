/*
  ==============================================================================

    GlobalControls.h
    Created: 30 Oct 2021 1:05:06am
    Author:  matkatmusic

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct Osc1GUI : juce::Component
{
    Osc1GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> osc1WaveSlider, osc1LevelSlider, osc1SemitonesSlider, osc1CentsSlider, osc1PWSlider, osc1SyncSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> osc1WaveSliderAttachment, osc1LevelSliderAttachment, osc1SemitonesSliderAttachment, osc1CentsSliderAttachment, osc1PWSliderAttachment, osc1SyncSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> osc1EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> osc1EnabledButtonAttachment;
};
