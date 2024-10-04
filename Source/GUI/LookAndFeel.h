/*
  ==============================================================================

    LookAndFeel.h
    Created: 30 Oct 2021 12:57:21am
    Author:  matkatmusic

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define USE_LIVE_CONSTANT false

#if USE_LIVE_CONSTANT
#define colorHelper(c) JUCE_LIVE_CONSTANT(c);
#else
#define colorHelper(c) c;
#endif

namespace ColorScheme
{
inline juce::Colour getSliderFillColor() { return colorHelper(juce::Colour(0xffa8a8a8)); }
inline juce::Colour getSliderRangeTextColor() { return juce::Colours::black; }
inline juce::Colour getSliderBorderColor() { return colorHelper(juce::Colour(0xff404040)); }
inline juce::Colour getModuleBackgroundColor() { return juce::Colours::grey; }
inline juce::Colour getModuleBorderColor() { return juce::Colours::black; }
inline juce::Colour getToggleButtonColor() { return juce::Colours::black; }
inline juce::Colour getTextColor() { return juce::Colours::black; }
inline juce::Colour getTickColor() { return colorHelper(juce::Colour(0xff404040)); }
}


struct LookAndFeel : juce::LookAndFeel_V4
{
    const int DialWidth = 45;
    const int LabelWidth = 45;
    const int LabelHeight = 15;
    const int TextBoxWidth = 42;
    const int TextBoxHeight = 15;
    
    const juce::Font Header1Font { juce::Font (16.0f, juce::Font::bold) };
    const juce::Font Header2Font { juce::Font (14.0f, juce::Font::bold) };
    const juce::Font TextFont { juce::Font (12.0f, juce::Font::plain) };
    
    LookAndFeel() {
        using namespace juce;
        
        auto& lnf = getDefaultLookAndFeel();
        lnf.setColour (Label::textColourId, Colours::black);
        lnf.setColour (Label::textWhenEditingColourId, Colours::white);
        lnf.setColour (Label::backgroundWhenEditingColourId, Colours::black);
        lnf.setColour (Label::outlineWhenEditingColourId, Colours::black);
        lnf.setColour (Slider::thumbColourId, Colours::white);
        lnf.setColour (Slider::textBoxTextColourId, Colours::black);
        lnf.setColour (Slider::textBoxBackgroundColourId, Colours::white);
        lnf.setColour (Slider::trackColourId, Colours::grey);
    }
    
    void drawRotarySlider (juce::Graphics&,
                           int x, int y, int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider&) override;
    
    void drawLinearSlider (juce::Graphics&,
                            int x, int y, int width, int height,
                            float sliderPos,
                            float minSliderPos,
                            float maxSliderPos,
                            const juce::Slider::SliderStyle,
                            juce::Slider&) override;
    
    void drawToggleButton (juce::Graphics&,
                            juce::ToggleButton&,
                            bool shouldDrawButtonAsHighlighted,
                            bool shouldDrawButtonAsDown) override;
    
    void drawTableHeaderBackground (juce::Graphics&,
                                    juce::TableHeaderComponent&) override;
    
    void drawTableHeaderColumn (juce::Graphics&, 
                                juce::TableHeaderComponent&,
                                const juce::String&, 
                                int /*columnId*/,
                                int width, int height, 
                                bool isMouseOver,
                                bool isMouseDown,
                                int columnFlags) override;
    
    juce::Font getLabelFont (juce::Label&) override;

};
