/*
  ==============================================================================

    Env2GUI.cpp
    Created: 13 May 2024 12:11:19am
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Env2GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
Env2GUI::Env2GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& env2AttackParam = getParamHelper(Names::ENV2_Attack);
    auto& env2DecayParam = getParamHelper(Names::ENV2_Decay);
    auto& env2SustainParam = getParamHelper(Names::ENV2_Sustain);
    auto& env2ReleaseParam = getParamHelper(Names::ENV2_Release);
    auto& env2KeyParam = getParamHelper(Names::ENV2_Key);
    auto& env2VelParam = getParamHelper(Names::ENV2_Vel);
    
    env2AttackSlider = std::make_unique<RSWT>(&env2AttackParam,
                                          "Attack");
    env2DecaySlider = std::make_unique<RSWT>(&env2DecayParam,
                                               "Decay");
    env2SustainSlider = std::make_unique<RSWT>(&env2SustainParam,
                                                "Sustain");
    env2ReleaseSlider = std::make_unique<RSWT>(&env2ReleaseParam,
                                           "Rel");
    env2KeySlider = std::make_unique<RSWT>(&env2KeyParam,
                                           "Key");
    env2VelSlider = std::make_unique<RSWT>(&env2VelParam,
                                           "Vel");
    env2EnabledButton = std::make_unique<juce::ToggleButton>("Env 2");
    
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(env2AttackSliderAttachment,
                         Names::ENV2_Attack,
                         *env2AttackSlider);
    
    makeAttachmentHelper(env2DecaySliderAttachment,
                         Names::ENV2_Decay,
                         *env2DecaySlider);
    
    makeAttachmentHelper(env2SustainSliderAttachment,
                         Names::ENV2_Sustain,
                         *env2SustainSlider);
    
    makeAttachmentHelper(env2ReleaseSliderAttachment,
                         Names::ENV2_Release,
                         *env2ReleaseSlider);
    
    makeAttachmentHelper(env2KeySliderAttachment,
                         Names::ENV2_Key,
                         *env2KeySlider);
    
    makeAttachmentHelper(env2VelSliderAttachment,
                         Names::ENV2_Vel,
                         *env2VelSlider);
    
    makeAttachmentHelper(env2EnabledButtonAttachment,
                         Names::ENV2_Enabled,
                         *env2EnabledButton);
    
    addAndMakeVisible(*env2AttackSlider);
    addAndMakeVisible(*env2DecaySlider);
    addAndMakeVisible(*env2SustainSlider);
    addAndMakeVisible(*env2ReleaseSlider);
    addAndMakeVisible(*env2KeySlider);
    addAndMakeVisible(*env2VelSlider);
    addAndMakeVisible(*env2EnabledButton);

}

void Env2GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void Env2GUI::resized()
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
    row0.items.add(FlexItem(*env2EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*env2AttackSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*env2DecaySlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*env2SustainSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*env2ReleaseSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*env2KeySlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*env2VelSlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}
