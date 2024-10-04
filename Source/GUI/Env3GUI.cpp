/*
  ==============================================================================

    Env3GUI.cpp
    Created: 13 May 2024 12:11:35am
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Env3GUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
Env3GUI::Env3GUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& env3AttackParam = getParamHelper(Names::ENV3_Attack);
    auto& env3DecayParam = getParamHelper(Names::ENV3_Decay);
    auto& env3SustainParam = getParamHelper(Names::ENV3_Sustain);
    auto& env3ReleaseParam = getParamHelper(Names::ENV3_Release);
    auto& env3KeyParam = getParamHelper(Names::ENV3_Key);
    auto& env3VelParam = getParamHelper(Names::ENV3_Vel);
    
    env3AttackSlider = std::make_unique<RSWT>(&env3AttackParam,
                                          "Attack");
    env3DecaySlider = std::make_unique<RSWT>(&env3DecayParam,
                                               "Decay");
    env3SustainSlider = std::make_unique<RSWT>(&env3SustainParam,
                                                "Sustain");
    env3ReleaseSlider = std::make_unique<RSWT>(&env3ReleaseParam,
                                           "Rel");
    env3KeySlider = std::make_unique<RSWT>(&env3KeyParam,
                                           "Key");
    env3VelSlider = std::make_unique<RSWT>(&env3VelParam,
                                           "Vel");
    env3EnabledButton = std::make_unique<juce::ToggleButton>("Amp Env");
    
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(env3AttackSliderAttachment,
                         Names::ENV3_Attack,
                         *env3AttackSlider);
    
    makeAttachmentHelper(env3DecaySliderAttachment,
                         Names::ENV3_Decay,
                         *env3DecaySlider);
    
    makeAttachmentHelper(env3SustainSliderAttachment,
                         Names::ENV3_Sustain,
                         *env3SustainSlider);
    
    makeAttachmentHelper(env3ReleaseSliderAttachment,
                         Names::ENV3_Release,
                         *env3ReleaseSlider);
    
    makeAttachmentHelper(env3KeySliderAttachment,
                         Names::ENV3_Key,
                         *env3KeySlider);
    
    makeAttachmentHelper(env3VelSliderAttachment,
                         Names::ENV3_Vel,
                         *env3VelSlider);
    
    makeAttachmentHelper(env3EnabledButtonAttachment,
                         Names::ENV3_Enabled,
                         *env3EnabledButton);
    
    addAndMakeVisible(*env3AttackSlider);
    addAndMakeVisible(*env3DecaySlider);
    addAndMakeVisible(*env3SustainSlider);
    addAndMakeVisible(*env3ReleaseSlider);
    addAndMakeVisible(*env3KeySlider);
    addAndMakeVisible(*env3VelSlider);
    addAndMakeVisible(*env3EnabledButton);

}

void Env3GUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
}

void Env3GUI::resized()
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
    row0.items.add(FlexItem(*env3EnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*env3AttackSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*env3DecaySlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*env3SustainSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*env3ReleaseSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*env3KeySlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*env3VelSlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(100));
}
