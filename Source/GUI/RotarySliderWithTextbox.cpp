/*
  ==============================================================================

    RotarySliderWithTextbox.cpp
    Created: 9 May 2024 11:19:05pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "RotarySliderWithTextbox.h"
#include "Utilities.h"
#include "LookAndFeel.h"

//==============================================================================
void RotarySliderWithTextbox::paint(juce::Graphics &g)
{
    using namespace juce;
    
    auto startAng = degreesToRadians(180.f + 45.f);
    auto endAng = degreesToRadians(180.f - 45.f) + MathConstants<float>::twoPi;
    
    auto range = getRange();
    
    auto sliderBounds = getSliderBounds();
    auto bounds = getLocalBounds();
    
    g.setFont(12.f);
    g.setColour(ColorScheme::getTextColor());
    g.drawFittedText(getName(), bounds.removeFromTop(getTextHeight() + 2), Justification::centredBottom, 1);
    
    getLookAndFeel().drawRotarySlider(g,
                                      sliderBounds.getX(),
                                      sliderBounds.getY(),
                                      sliderBounds.getWidth(),
                                      sliderBounds.getHeight(),
                                      static_cast<float>(jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0)),
                                      startAng,
                                      endAng,
                                      *this);
}

juce::Rectangle<int> RotarySliderWithTextbox::getSliderBounds() const
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(static_cast<int>(getTextHeight() * 1.5));
    
    auto size = 45; //juce::jmin(bounds.getWidth(), bounds.getHeight());
    
    size -= static_cast<int>(getTextHeight() * 1.5);
    juce::Rectangle<int> r;
    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), 0);
    r.setY(bounds.getY());
    
    return r;
    
}

juce::String RotarySliderWithTextbox::getDisplayString() const
{
    if( auto* choiceParam = dynamic_cast<juce::AudioParameterChoice*>(param) )
        return choiceParam->getCurrentChoiceName();
    
    juce::String str;
    bool addK = false;
    
    if( auto* floatParam = dynamic_cast<juce::AudioParameterFloat*>(param) )
    {
        auto val = getValue();
        
        addK = GMSQ1::truncateKiloValue(val);
        
        str = juce::String(val, (addK ? 2 : 0));
    }
    else
    {
        jassertfalse; //this shouldn't happen!
    }
    
    return str;
}

void RotarySliderWithTextbox::changeParam(juce::RangedAudioParameter *p)
{
    param = p;
    repaint();
}
//==============================================================================
