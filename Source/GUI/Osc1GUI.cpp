/*
  ==============================================================================

    GlobalControls.cpp
    Created: 30 Oct 2021 1:05:06am
    Author:  matkatmusic

  ==============================================================================
*/

#include "Osc1GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
Osc1GUI::Osc1GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& osc1WaveParam = getParamHelper(Names::Osc1_Wave);
    auto& osc1SemitonesParam = getParamHelper(Names::Osc1_Semitones);
    auto& osc1CentsParam = getParamHelper(Names::Osc1_Cents);
    auto& osc1LevelParam = getParamHelper(Names::Osc1_Level);
    auto& osc1PulseWidthParam = getParamHelper(Names::Osc1_PW);
    auto& osc1SyncParam = getParamHelper(Names::Osc1_Sync);
    
    osc1WaveSlider = std::make_unique<RSWT>(&osc1WaveParam,
                                          "Wave");
    osc1SemitonesSlider = std::make_unique<RSWT>(&osc1SemitonesParam,
                                               "Semi");
    osc1CentsSlider = std::make_unique<RSWT>(&osc1CentsParam,
                                                "Cents");
    osc1LevelSlider = std::make_unique<RSWT>(&osc1LevelParam,
                                           "Level");
    osc1PWSlider = std::make_unique<RSWT>(&osc1PulseWidthParam,
                                           "PW");
    osc1SyncSlider = std::make_unique<RSWT>(&osc1SyncParam,
                                           "Sync");
    osc1EnabledButton = std::make_unique<juce::ToggleButton>("Osc 1");
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(osc1WaveSliderAttachment,
                         Names::Osc1_Wave,
                         *osc1WaveSlider);
    
    makeAttachmentHelper(osc1SemitonesSliderAttachment,
                         Names::Osc1_Semitones,
                         *osc1SemitonesSlider);
    
    makeAttachmentHelper(osc1CentsSliderAttachment,
                         Names::Osc1_Cents,
                         *osc1CentsSlider);
    
    makeAttachmentHelper(osc1LevelSliderAttachment,
                         Names::Osc1_Level,
                         *osc1LevelSlider);
    
    makeAttachmentHelper(osc1PWSliderAttachment,
                         Names::Osc1_PW,
                         *osc1PWSlider);
    
    makeAttachmentHelper(osc1SyncSliderAttachment,
                         Names::Osc1_Sync,
                         *osc1SyncSlider);
    
    makeAttachmentHelper(osc1EnabledButtonAttachment,
                         Names::Osc1_Enabled,
                         *osc1EnabledButton);
    
    addAndMakeVisible(*osc1WaveSlider);
    addAndMakeVisible(*osc1SemitonesSlider);
    addAndMakeVisible(*osc1CentsSlider);
    addAndMakeVisible(*osc1LevelSlider);
    addAndMakeVisible(*osc1PWSlider);
    addAndMakeVisible(*osc1SyncSlider);
    addAndMakeVisible(*osc1EnabledButton);
}

void Osc1GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void Osc1GUI::resized()
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
    row0.items.add(FlexItem(*osc1EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*osc1WaveSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc1SemitonesSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc1CentsSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*osc1LevelSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc1PWSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc1SyncSlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}
