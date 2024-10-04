/*
  ==============================================================================

    LFO2GUI.h
    Created: 19 May 2024 12:10:56am
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

struct LFO2GUI : juce::Component
{
    LFO2GUI(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    juce::String label;
    
    using RSWT = RotarySliderWithTextbox;
    std::unique_ptr<RSWT> lfo2SourceSlider, lfo2DestSlider, lfo2WaveSlider, lfo2RateSlider, lfo2GainSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> lfo2SourceSliderAttachment, lfo2DestSliderAttachment, lfo2WaveSliderAttachment, lfo2RateSliderAttachment, lfo2GainSliderAttachment;
    
    using Button = juce::ToggleButton;
    std::unique_ptr<Button> lfo2ResetButton, lfo2EnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> lfo2ResetButtonAttachment, lfo2EnabledButtonAttachment;
};
