/*
  ==============================================================================

    GlobalControls.cpp
    Created: 30 Oct 2021 1:05:06am
    Author:  matkatmusic

  ==============================================================================
*/

#include "Env1GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
Env1GUI::Env1GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& env1AttackParam = getParamHelper(Names::ENV1_Attack);
    auto& env1DecayParam = getParamHelper(Names::ENV1_Decay);
    auto& env1SustainParam = getParamHelper(Names::ENV1_Sustain);
    auto& env1ReleaseParam = getParamHelper(Names::ENV1_Release);
    auto& env1KeyParam = getParamHelper(Names::ENV1_Key);
    auto& env1VelParam = getParamHelper(Names::ENV1_Vel);
    
    env1AttackSlider = std::make_unique<RSWT>(&env1AttackParam,
                                          "Attack");
    env1DecaySlider = std::make_unique<RSWT>(&env1DecayParam,
                                               "Decay");
    env1SustainSlider = std::make_unique<RSWT>(&env1SustainParam,
                                                "Sustain");
    env1ReleaseSlider = std::make_unique<RSWT>(&env1ReleaseParam,
                                           "Rel");
    env1KeySlider = std::make_unique<RSWT>(&env1KeyParam,
                                           "Key");
    env1VelSlider = std::make_unique<RSWT>(&env1VelParam,
                                           "Vel");
    
    env1EnabledButton = std::make_unique<juce::ToggleButton>("Env 1");
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(env1AttackSliderAttachment,
                         Names::ENV1_Attack,
                         *env1AttackSlider);
    
    makeAttachmentHelper(env1DecaySliderAttachment,
                         Names::ENV1_Decay,
                         *env1DecaySlider);
    
    makeAttachmentHelper(env1SustainSliderAttachment,
                         Names::ENV1_Sustain,
                         *env1SustainSlider);
    
    makeAttachmentHelper(env1ReleaseSliderAttachment,
                         Names::ENV1_Release,
                         *env1ReleaseSlider);
    
    makeAttachmentHelper(env1KeySliderAttachment,
                         Names::ENV1_Key,
                         *env1KeySlider);
    
    makeAttachmentHelper(env1VelSliderAttachment,
                         Names::ENV1_Vel,
                         *env1VelSlider);
    
    makeAttachmentHelper(env1EnabledButtonAttachment,
                         Names::ENV1_Enabled,
                         *env1EnabledButton);
    
    addAndMakeVisible(*env1AttackSlider);
    addAndMakeVisible(*env1DecaySlider);
    addAndMakeVisible(*env1SustainSlider);
    addAndMakeVisible(*env1ReleaseSlider);
    addAndMakeVisible(*env1KeySlider);
    addAndMakeVisible(*env1VelSlider);
    addAndMakeVisible(*env1EnabledButton);

}

void Env1GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void Env1GUI::resized()
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
    row0.items.add(FlexItem(*env1EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*env1AttackSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*env1DecaySlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*env1SustainSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*env1ReleaseSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*env1KeySlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*env1VelSlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}
