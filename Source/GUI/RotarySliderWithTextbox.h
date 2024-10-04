/*
  ==============================================================================

     RotarySliderWithTextbox.h
     Created: 9 May 2024 11:19:05pm
     Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct RotarySliderWithTextbox : juce::Slider
{
    RotarySliderWithTextbox(juce::RangedAudioParameter* rap,
                           const juce::String& title) :
    juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                 juce::Slider::TextEntryBoxPosition::NoTextBox),
    param(rap),
    suffix()
    {
        setName(title);
    }
    
    struct LabelPos
    {
        float pos;
        juce::String label;
    };
    
    juce::Array<LabelPos> labels;
    
    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const { return 12; }
    virtual juce::String getDisplayString() const;
    
    void changeParam(juce::RangedAudioParameter* p);
protected:
    juce::RangedAudioParameter* param;
    juce::String suffix;
};
