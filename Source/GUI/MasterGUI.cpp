/*
  ==============================================================================

    MasterGUI.cpp
    Created: 20 May 2024 11:33:10pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "MasterGUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
MasterGUI::MasterGUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return GMSQ1::getParam(apvts, params, name);
    };
    
    auto& gainParam = getParamHelper(Names::Master_Gain);
    auto& pitchBendParam = getParamHelper(Names::Pitch_Bend);
    auto& nrOfVoicesParam = getParamHelper(Names::Nr_Of_Voices);
    
    gainSlider = std::make_unique<RSWT>(&gainParam,
                                          "Level");
    pitchBendSlider = std::make_unique<RSWT>(&pitchBendParam,
                                               "Pitch bend");
    nrOfVoicesSlider = std::make_unique<RSWT>(&nrOfVoicesParam,
                                                "Voices");
    masterEnabledButton = std::make_unique<juce::ToggleButton>("Master");
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(gainSliderAttachment,
                         Names::Master_Gain,
                         *gainSlider);
    
    makeAttachmentHelper(pitchBendSliderAttachment,
                         Names::Pitch_Bend,
                         *pitchBendSlider);
    
    makeAttachmentHelper(nrOfVoicesSliderAttachment,
                         Names::Nr_Of_Voices,
                         *nrOfVoicesSlider);
    
    makeAttachmentHelper(masterEnabledButtonAttachment,
                         Names::Master_Enabled,
                         *masterEnabledButton);
    
    addAndMakeVisible(*gainSlider);
    addAndMakeVisible(*pitchBendSlider);
    addAndMakeVisible(*nrOfVoicesSlider);
    addAndMakeVisible(*masterEnabledButton);
}

void MasterGUI::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
    
    juce::Rectangle<int> componentArea (0, 0, getWidth(), getHeight());
    juce::Rectangle<int> titleArea (0, 10, componentArea.getWidth(), lnf.LabelHeight);
    g.drawRect(componentArea);
    g.setFont(lnf.Header2Font);
    g.drawText("Master", titleArea, juce::Justification::centredTop);
}

void MasterGUI::resized()
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
    row0.items.add(FlexItem(*masterEnabledButton).withHeight(50).withFlex(1.f));
    row0.items.add(endCap);
    
    row0.performLayout(bounds);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*gainSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*pitchBendSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*nrOfVoicesSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds.withTrimmedTop(30));
}
