/*
  ==============================================================================

    FilterGUI.cpp
    Created: 9 May 2024 10:25:58pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "FilterGUI.h"


//==============================================================================
FilterGUI::FilterGUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& filterModeParam = getParamHelper(Names::Filter_Mode);
    auto& filterCutoffParam = getParamHelper(Names::Filter_Cutoff);
    auto& filterResonanceParam = getParamHelper(Names::Filter_Res);
    auto& filterVelParam = getParamHelper(Names::Filter_Vel);
    auto& filterEnvParam = getParamHelper(Names::Filter_Env);
    auto& filterKeyParam = getParamHelper(Names::Filter_Key);

    
    filterModeSlider = std::make_unique<RSWT>(&filterModeParam,
                                          "Mode");
    filterCutoffSlider = std::make_unique<RSWT>(&filterCutoffParam,
                                               "Cutoff");
    filterResonanceSlider = std::make_unique<RSWT>(&filterResonanceParam,
                                               "Resonance");
    filterVelSlider = std::make_unique<RSWT>(&filterVelParam,
                                          "Vel");
    filterEnvSlider = std::make_unique<RSWT>(&filterEnvParam,
                                               "Env 1");
    filterKeySlider = std::make_unique<RSWT>(&filterKeyParam,
                                               "Key");
    filterEnabledButton = std::make_unique<juce::ToggleButton>("Filter");
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(filterModeSliderAttachment,
                         Names::Filter_Mode,
                         *filterModeSlider);
    
    makeAttachmentHelper(filterCutoffSliderAttachment,
                         Names::Filter_Cutoff,
                         *filterCutoffSlider);
    
    makeAttachmentHelper(filterResonanceSliderAttachment,
                         Names::Filter_Res,
                         *filterResonanceSlider);
    
    makeAttachmentHelper(filterVelSliderAttachment,
                         Names::Filter_Vel,
                         *filterVelSlider);
    
    makeAttachmentHelper(filterEnvSliderAttachment,
                         Names::Filter_Env,
                         *filterEnvSlider);
    
    makeAttachmentHelper(filterKeySliderAttachment,
                         Names::Filter_Key,
                         *filterKeySlider);
    
    makeAttachmentHelper(filterEnabledButtonAttachment,
                         Names::Filter_Enabled,
                         *filterEnabledButton);
    
    addAndMakeVisible(*filterModeSlider);
    addAndMakeVisible(*filterCutoffSlider);
    addAndMakeVisible(*filterResonanceSlider);
    addAndMakeVisible(*filterVelSlider);
    addAndMakeVisible(*filterEnvSlider);
    addAndMakeVisible(*filterKeySlider);
    addAndMakeVisible(*filterEnabledButton);
}

void FilterGUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void FilterGUI::resized()
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
    row0.items.add(FlexItem(*filterEnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*filterModeSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*filterCutoffSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*filterResonanceSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*filterVelSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*filterEnvSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*filterKeySlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}
