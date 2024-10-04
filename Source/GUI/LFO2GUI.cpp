/*
  ==============================================================================

    LFO2GUI.cpp
    Created: 19 May 2024 12:10:56am
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "LFO2GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

LFO2GUI::LFO2GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& lfo2SourceParam = getParamHelper(Names::LFO2_Source);
    auto& lfo2DestParam = getParamHelper(Names::LFO2_Dest);
    auto& lfo2WaveParam = getParamHelper(Names::LFO2_Wave);
    auto& lfo2RateParam = getParamHelper(Names::LFO2_Rate);
    auto& lfo2GainParam = getParamHelper(Names::LFO2_Gain);
    
    lfo2SourceSlider = std::make_unique<RSWT>(&lfo2SourceParam,
                                          "Source");
    lfo2DestSlider = std::make_unique<RSWT>(&lfo2DestParam,
                                               "Dest");
    lfo2WaveSlider = std::make_unique<RSWT>(&lfo2WaveParam,
                                                "Wave");
    lfo2RateSlider = std::make_unique<RSWT>(&lfo2RateParam,
                                           "Rate");
    lfo2GainSlider = std::make_unique<RSWT>(&lfo2GainParam,
                                           "Gain");
    lfo2ResetButton = std::make_unique<juce::ToggleButton>("Reset");
    lfo2EnabledButton = std::make_unique<juce::ToggleButton>("LFO 2");
    
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(lfo2SourceSliderAttachment,
                         Names::LFO2_Source,
                         *lfo2SourceSlider);
    
    makeAttachmentHelper(lfo2DestSliderAttachment,
                         Names::LFO2_Dest,
                         *lfo2DestSlider);
    
    makeAttachmentHelper(lfo2WaveSliderAttachment,
                         Names::LFO2_Wave,
                         *lfo2WaveSlider);
    
    makeAttachmentHelper(lfo2RateSliderAttachment,
                         Names::LFO2_Rate,
                         *lfo2RateSlider);
    
    makeAttachmentHelper(lfo2GainSliderAttachment,
                         Names::LFO2_Gain,
                         *lfo2GainSlider);
    
    makeAttachmentHelper(lfo2ResetButtonAttachment,
                         Names::LFO2_Reset,
                         *lfo2ResetButton);
    
    makeAttachmentHelper(lfo2EnabledButtonAttachment,
                         Names::LFO2_Enabled,
                         *lfo2EnabledButton);
    
    addAndMakeVisible(*lfo2SourceSlider);
    addAndMakeVisible(*lfo2DestSlider);
    addAndMakeVisible(*lfo2WaveSlider);
    addAndMakeVisible(*lfo2RateSlider);
    addAndMakeVisible(*lfo2GainSlider);
    addAndMakeVisible(*lfo2ResetButton);
    addAndMakeVisible(*lfo2EnabledButton);
}

void LFO2GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void LFO2GUI::resized()
{
    auto bounds = getLocalBounds().reduced(5);
    using namespace juce;
    
    auto spacer = FlexItem().withWidth(4);
    auto endCap = FlexItem().withWidth(6);
    
    FlexBox row0;
    row0.flexDirection = FlexBox::Direction::row;
    row0.flexWrap = FlexBox::Wrap::noWrap;
    
    row0.items.add(endCap);
    row0.items.add(FlexItem(*lfo2EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*lfo2SourceSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*lfo2DestSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*lfo2WaveSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*lfo2RateSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*lfo2GainSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*lfo2ResetButton).withHeight(95).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}

