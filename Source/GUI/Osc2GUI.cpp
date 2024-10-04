/*
  ==============================================================================

    Osc2GUI.cpp
    Created: 9 May 2024 11:18:50pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Osc2GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
Osc2GUI::Osc2GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& osc2WaveParam = getParamHelper(Names::Osc2_Wave);
    auto& osc2SemitonesParam = getParamHelper(Names::Osc2_Semitones);
    auto& osc2CentsParam = getParamHelper(Names::Osc2_Cents);
    auto& osc2LevelParam = getParamHelper(Names::Osc2_Level);
    auto& osc2PWParam = getParamHelper(Names::Osc2_PW);
    auto& osc2FMParam = getParamHelper(Names::Osc2_FM);

    
    osc2WaveSlider = std::make_unique<RSWT>(&osc2WaveParam,
                                          "Wave");
    osc2SemitonesSlider = std::make_unique<RSWT>(&osc2SemitonesParam,
                                               "Semi");
    osc2CentsSlider = std::make_unique<RSWT>(&osc2CentsParam,
                                                "Cents");
    osc2LevelSlider = std::make_unique<RSWT>(&osc2LevelParam,
                                           "Level");
    osc2PWSlider = std::make_unique<RSWT>(&osc2PWParam,
                                           "PW");
    osc2FMSlider = std::make_unique<RSWT>(&osc2FMParam,
                                           "FM");
    
    osc2EnabledButton = std::make_unique<juce::ToggleButton>("Osc 2");
    
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(osc2WaveSliderAttachment,
                         Names::Osc2_Wave,
                         *osc2WaveSlider);
    
    makeAttachmentHelper(osc2SemitonesSliderAttachment,
                         Names::Osc2_Semitones,
                         *osc2SemitonesSlider);
    
    makeAttachmentHelper(osc2CentsSliderAttachment,
                         Names::Osc2_Cents,
                         *osc2CentsSlider);
    
    makeAttachmentHelper(osc2LevelSliderAttachment,
                         Names::Osc2_Level,
                         *osc2LevelSlider);
    
    makeAttachmentHelper(osc2PWSliderAttachment,
                         Names::Osc2_PW,
                         *osc2PWSlider);
    
    makeAttachmentHelper(osc2FMSliderAttachment,
                         Names::Osc2_FM,
                         *osc2FMSlider);
    
    makeAttachmentHelper(osc2EnabledButtonAttachment,
                         Names::Osc2_Enabled,
                         *osc2EnabledButton);
    
    addAndMakeVisible(*osc2WaveSlider);
    addAndMakeVisible(*osc2SemitonesSlider);
    addAndMakeVisible(*osc2CentsSlider);
    addAndMakeVisible(*osc2LevelSlider);
    addAndMakeVisible(*osc2PWSlider);
    addAndMakeVisible(*osc2FMSlider);
    addAndMakeVisible(*osc2EnabledButton);
}

void Osc2GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void Osc2GUI::resized()
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
    row0.items.add(FlexItem(*osc2EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*osc2WaveSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc2SemitonesSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc2CentsSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*osc2LevelSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc2PWSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc2FMSlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}
