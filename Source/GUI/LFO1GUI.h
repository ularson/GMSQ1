/*
  ==============================================================================

    LFO1GUI.h
    Created: 18 May 2024 11:38:04pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct LFO1GUI : juce::Component
{
    LFO1GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    juce::String label;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> lfo1SourceSlider, lfo1DestSlider, lfo1WaveSlider, lfo1RateSlider, lfo1GainSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> lfo1SourceSliderAttachment, lfo1DestSliderAttachment, lfo1WaveSliderAttachment, lfo1RateSliderAttachment, lfo1GainSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> lfo1ResetButton, lfo1EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> lfo1ResetButtonAttachment, lfo1EnabledButtonAttachment;
};
