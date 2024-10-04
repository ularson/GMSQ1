/*
  ==============================================================================

    LFO1GUI.cpp
    Created: 18 May 2024 11:38:04pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "LFO1GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

LFO1GUI::LFO1GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& lfo1SourceParam = getParamHelper(Names::LFO1_Source);
    auto& lfo1DestParam = getParamHelper(Names::LFO1_Dest);
    auto& lfo1WaveParam = getParamHelper(Names::LFO1_Wave);
    auto& lfo1RateParam = getParamHelper(Names::LFO1_Rate);
    auto& lfo1GainParam = getParamHelper(Names::LFO1_Gain);
    
    lfo1SourceSlider = std::make_unique<RSWT>(&lfo1SourceParam,
                                          "Source");
    lfo1DestSlider = std::make_unique<RSWT>(&lfo1DestParam,
                                               "Dest");
    lfo1WaveSlider = std::make_unique<RSWT>(&lfo1WaveParam,
                                                "Wave");
    lfo1RateSlider = std::make_unique<RSWT>(&lfo1RateParam,
                                           "Rate");
    lfo1GainSlider = std::make_unique<RSWT>(&lfo1GainParam,
                                           "Gain");
    lfo1ResetButton = std::make_unique<juce::ToggleButton>("Reset");
    lfo1EnabledButton = std::make_unique<juce::ToggleButton>("LFO 1");
    
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(lfo1SourceSliderAttachment,
                         Names::LFO1_Source,
                         *lfo1SourceSlider);
    
    makeAttachmentHelper(lfo1DestSliderAttachment,
                         Names::LFO1_Dest,
                         *lfo1DestSlider);
    
    makeAttachmentHelper(lfo1WaveSliderAttachment,
                         Names::LFO1_Wave,
                         *lfo1WaveSlider);
    
    makeAttachmentHelper(lfo1RateSliderAttachment,
                         Names::LFO1_Rate,
                         *lfo1RateSlider);
    
    makeAttachmentHelper(lfo1GainSliderAttachment,
                         Names::LFO1_Gain,
                         *lfo1GainSlider);
    
    makeAttachmentHelper(lfo1ResetButtonAttachment,
                         Names::LFO1_Reset,
                         *lfo1ResetButton);
    
    makeAttachmentHelper(lfo1EnabledButtonAttachment,
                         Names::LFO1_Enabled,
                         *lfo1EnabledButton);
    
    
    addAndMakeVisible(*lfo1SourceSlider);
    addAndMakeVisible(*lfo1DestSlider);
    addAndMakeVisible(*lfo1WaveSlider);
    addAndMakeVisible(*lfo1RateSlider);
    addAndMakeVisible(*lfo1GainSlider);
    addAndMakeVisible(*lfo1ResetButton);
    addAndMakeVisible(*lfo1EnabledButton);
}

void LFO1GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void LFO1GUI::resized()
{
    auto bounds = getLocalBounds().reduced(5);
    using namespace juce;
    
    auto spacer = FlexItem().withWidth(4);
    auto endCap = FlexItem().withWidth(6);
    
    FlexBox row0;
    row0.flexDirection = FlexBox::Direction::row;
    row0.FlexBox::justifyContent = FlexBox::JustifyContent::center;
    row0.flexWrap = FlexBox::Wrap::wrap;
    
    row0.items.add(endCap);
    row0.items.add(FlexItem(*lfo1EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*lfo1SourceSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*lfo1DestSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*lfo1WaveSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*lfo1RateSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*lfo1GainSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*lfo1ResetButton).withHeight(95).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}

