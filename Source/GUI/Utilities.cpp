/*
  ==============================================================================

    Utilities.cpp
    Created: 13 Apr 2024 11:14:02pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Utilities.h"

namespace GMSQ1
{
    juce::String getValString(const juce::RangedAudioParameter& param,
                              bool getLow,
                              juce::String suffix)
    {
        juce::String str;
        
        auto val = getLow ? param.getNormalisableRange().start :
        param.getNormalisableRange().end;
        
        bool useK = truncateKiloValue(val);
        str << val;
        
        if( useK )
            str << "k";
        
        str << suffix;
        
        return str;
    }

    juce::Rectangle<int> getModuleBackgroundArea(juce::Rectangle<int> bounds)
    {
        bounds.reduce(3, 3);
        
        return bounds;
    }

    void drawModuleBackground(juce::Graphics &g,
                              juce::Rectangle<int> bounds)
    {
        using namespace juce;
        g.setColour(ColorScheme::getModuleBorderColor());
        g.fillAll();
        
        auto localBounds = bounds;
        
        bounds.reduce(3, 3);
        g.setColour(ColorScheme::getModuleBackgroundColor());
        g.fillRoundedRectangle(bounds.toFloat(), 3);
        
        g.drawRect(localBounds);
    }
}
