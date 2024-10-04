/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 30 Oct 2021 12:57:21am
    Author:  matkatmusic

  ==============================================================================
*/

#include "LookAndFeel.h"
#include "RotarySliderWithTextbox.h"

void LookAndFeel::drawRotarySlider(juce::Graphics & g,
                                   int x,
                                   int y,
                                   int width,
                                   int height,
                                   float sliderPosProportional,
                                   float rotaryStartAngle,
                                   float rotaryEndAngle,
                                   juce::Slider & slider)
{
    using namespace juce;
    
    auto bounds = Rectangle<float>(x, y, width, height);
    
    auto enabled = slider.isEnabled();
    
    g.setColour(enabled ? ColorScheme::getSliderFillColor() : Colours::darkgrey );
    g.fillEllipse(bounds);
    
    g.setColour(enabled ? ColorScheme::getSliderBorderColor() : Colours::grey);
    g.drawEllipse(bounds, 1.f);
    
    if( auto* rswt = dynamic_cast<RotarySliderWithTextbox*>(&slider))
    {
        auto center = bounds.getCentre();
        Path p;
        
        Rectangle<float> r;
        r.setLeft(center.getX() - 1);
        r.setRight(center.getX() + 1);
        r.setTop(bounds.getY());
        r.setBottom(center.getY());
        
        p.addRoundedRectangle(r, 2.f);
        
        jassert(rotaryStartAngle < rotaryEndAngle);
        
        auto sliderAngRad = jmap(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);
        
        p.applyTransform(AffineTransform().rotated(sliderAngRad, center.getX(), center.getY()));
        
        g.fillPath(p);
        
        g.setFont(rswt->getTextHeight());
        auto text = rswt->getDisplayString();
        auto strWidth = g.getCurrentFont().getStringWidth(text);
        
        r.setSize(strWidth + 4, rswt->getTextHeight() + 2);
        r.setCentre(bounds.getCentre());
        r.setY(50);
        
        g.setColour(enabled ? ColorScheme::getTextColor() : Colours::lightgrey);
        g.drawFittedText(text, r.toNearestInt(), juce::Justification::centred, 1);
    }
}

void LookAndFeel::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    using namespace juce;
    
    if (slider.isBar())
    {
        g.setColour (ColorScheme::getSliderFillColor());
        g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), (float) y + 0.5f, sliderPos - (float) x, (float) height - 1.0f)
                                          : Rectangle<float> ((float) x + 0.5f, sliderPos, (float) width - 1.0f, (float) y + ((float) height - sliderPos)));

        drawLinearSliderOutline (g, x, y, width, height, style, slider);
    }
    else
    {
        auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

        Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

        Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : (float) y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (slider.findColour (Slider::backgroundColourId));
        g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : (float) width * 0.5f,
                         slider.isHorizontal() ? (float) height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : (float) width * 0.5f,
                               slider.isHorizontal() ? (float) height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : (float) width * 0.5f,
                         slider.isHorizontal() ? (float) height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
            auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = getSliderThumbRadius (slider);

        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
        g.setColour (slider.findColour (Slider::trackColourId));
        g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        if (! isTwoVal)
        {
            g.setColour (slider.findColour (Slider::thumbColourId));
            g.fillEllipse (Rectangle<float> (static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre (isThreeVal ? thumbPoint : maxPoint));
        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin (trackWidth, (slider.isHorizontal() ? (float) height : (float) width) * 0.4f);
            auto pointerColour = slider.findColour (Slider::thumbColourId);

            if (slider.isHorizontal())
            {
                drawPointer (g, minSliderPos - sr,
                             jmax (0.0f, (float) y + (float) height * 0.5f - trackWidth * 2.0f),
                             trackWidth * 2.0f, pointerColour, 2);

                drawPointer (g, maxSliderPos - trackWidth,
                             jmin ((float) (y + height) - trackWidth * 2.0f, (float) y + (float) height * 0.5f),
                             trackWidth * 2.0f, pointerColour, 4);
            }
            else
            {
                drawPointer (g, jmax (0.0f, (float) x + (float) width * 0.5f - trackWidth * 2.0f),
                             minSliderPos - trackWidth,
                             trackWidth * 2.0f, pointerColour, 1);

                drawPointer (g, jmin ((float) (x + width) - trackWidth * 2.0f, (float) x + (float) width * 0.5f), maxSliderPos - sr,
                             trackWidth * 2.0f, pointerColour, 3);
            }
        }

        if (slider.isBar())
            drawLinearSliderOutline (g, x, y, width, height, style, slider);
    }
}

void LookAndFeel::drawToggleButton (juce::Graphics& g, juce::ToggleButton& button,
                                       bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    using namespace juce;
    
    setColour (ToggleButton::textColourId, juce::Colours::red);
    setColour (ToggleButton::tickColourId, ColorScheme::getTickColor());
    setColour (ToggleButton::tickDisabledColourId, ColorScheme::getSliderBorderColor());
    
    auto fontSize = jmin (15.0f, (float) button.getHeight() * 0.75f);
    auto tickWidth = fontSize * 1.1f;

    drawTickBox (g, button, 15.0f, ((float) button.getHeight() - tickWidth - 30) * 0.5f,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 shouldDrawButtonAsHighlighted,
                 shouldDrawButtonAsDown);

    g.setColour (ColorScheme::getTextColor());
    g.setFont (TextFont);

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    g.drawFittedText (button.getButtonText(),
                      button.getLocalBounds().withTrimmedTop(3),
                      Justification::centredTop, 0);
}

void LookAndFeel::drawTableHeaderBackground (juce::Graphics& g, juce::TableHeaderComponent& header)
{
    auto area = header.getLocalBounds();
    
    g.setColour (ColorScheme::getModuleBackgroundColor());
    g.fillRect (area);
    
    g.setColour (ColorScheme::getSliderBorderColor());
    g.fillRect (area.removeFromTop (1));
    g.fillRect (area.removeFromBottom (1));
    g.fillRect (area.removeFromLeft (1));
    g.fillRect (area.removeFromRight (1));
    
    int numColumns = header.getNumColumns (true);
    
    for (int i = numColumns - 1; --i >= 0;)
        g.fillRect (header.getColumnPosition (i).removeFromRight (1));
}

void LookAndFeel::drawTableHeaderColumn (juce::Graphics& g, juce::TableHeaderComponent& header,
                                         const juce::String& columnName, int /*columnId*/,
                                        int width, int height, bool isMouseOver, bool isMouseDown,
                                        int columnFlags)
{
    using namespace juce;
    
    auto highlightColour = header.findColour (TableHeaderComponent::highlightColourId);

    if (isMouseDown)
        g.fillAll (highlightColour);
    else if (isMouseOver)
        g.fillAll (highlightColour.withMultipliedAlpha (0.625f));

    Rectangle<int> area (width, height);
    area.reduce (4, 0);

    g.setColour (header.findColour (TableHeaderComponent::textColourId));
    g.setFont (TextFont);
    g.drawFittedText (columnName, area, Justification::centredLeft, 1);
}

juce::Font LookAndFeel::getLabelFont (juce::Label& label)
{
    return juce::Font(TextFont);
}
