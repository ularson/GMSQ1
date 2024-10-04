/*
  ==============================================================================

    Osc3GUI.cpp
    Created: 9 May 2024 11:19:05pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Osc3GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
Osc3GUI::Osc3GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& osc3WaveParam = getParamHelper(Names::Osc3_Wave);
    auto& osc3SemitonesParam = getParamHelper(Names::Osc3_Semitones);
    auto& osc3CentsParam = getParamHelper(Names::Osc3_Cents);
    auto& osc3LevelParam = getParamHelper(Names::Osc3_Level);
    auto& osc3PWParam = getParamHelper(Names::Osc3_PW);

    
    osc3WaveSlider = std::make_unique<RSWT>(&osc3WaveParam,
                                          "Wave");
    osc3SemitonesSlider = std::make_unique<RSWT>(&osc3SemitonesParam,
                                               "Semi");
    osc3CentsSlider = std::make_unique<RSWT>(&osc3CentsParam,
                                                "Cents");
    osc3LevelSlider = std::make_unique<RSWT>(&osc3LevelParam,
                                           "Level");
    osc3PWSlider = std::make_unique<RSWT>(&osc3PWParam,
                                           "PW");
    osc3EnabledButton = std::make_unique<juce::ToggleButton>("Osc 3");
    
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(osc3WaveSliderAttachment,
                         Names::Osc3_Wave,
                         *osc3WaveSlider);
    
    makeAttachmentHelper(osc3SemitonesSliderAttachment,
                         Names::Osc3_Semitones,
                         *osc3SemitonesSlider);
    
    makeAttachmentHelper(osc3CentsSliderAttachment,
                         Names::Osc3_Cents,
                         *osc3CentsSlider);
    
    makeAttachmentHelper(osc3LevelSliderAttachment,
                         Names::Osc3_Level,
                         *osc3LevelSlider);
    
    makeAttachmentHelper(osc3PWSliderAttachment,
                         Names::Osc3_PW,
                         *osc3PWSlider);
    
    makeAttachmentHelper(osc3EnabledEnabledAttachment,
                         Names::Osc3_Enabled,
                         *osc3EnabledButton);
    
    addAndMakeVisible(*osc3WaveSlider);
    addAndMakeVisible(*osc3SemitonesSlider);
    addAndMakeVisible(*osc3CentsSlider);
    addAndMakeVisible(*osc3LevelSlider);
    addAndMakeVisible(*osc3PWSlider);
    addAndMakeVisible(*osc3EnabledButton);
}

void Osc3GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void Osc3GUI::resized()
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
    row0.items.add(FlexItem(*osc3EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*osc3WaveSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc3SemitonesSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc3CentsSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*osc3LevelSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc3PWSlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}
