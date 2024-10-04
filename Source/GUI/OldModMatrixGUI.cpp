/*
  ==============================================================================

    ModMatrix.cpp
    Created: 19 May 2024 10:20:18pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "ModMatrixGUI.h"
#include "LookAndFeel.h"
#include "../DSP/Params.h"
#include "Utilities.h"

//==============================================================================
ModMatrixGUI::ModMatrixGUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts](const auto& name) -> auto&
    {
        return NewSynth::getParam(apvts, params, name);
    };
    
    setLookAndFeel(&lnf);
    
    modMatrixTable.setModel(this);
    modMatrixTable.autoSizeAllColumns();
    modMatrixTable.getViewport()->setScrollBarsShown(true, false);
    modMatrixTable.getHeader().addColumn("Env 1", 1, colWidth);
    modMatrixTable.getHeader().addColumn("Env 2", 2, colWidth);
    modMatrixTable.getHeader().addColumn("Lfo 1", 3, colWidth);
    modMatrixTable.getHeader().addColumn("LFO 2", 4, colWidth);
    modMatrixTable.getHeader().addColumn("Vel", 5, colWidth);
    modMatrixTable.getHeader().addColumn("Mod", 6, colWidth);
    addAndMakeVisible(&modMatrixTable);
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        NewSynth::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    auto& osc1PitchEnv1Param = getParamHelper(Names::Osc1_Pitch_Env1);
    auto& osc1PitchEnv2Param = getParamHelper(Names::Osc1_Pitch_Env2);
    auto& osc1PitchLfo1Param = getParamHelper(Names::Osc1_Pitch_Lfo1);
    auto& osc1PitchLfo2Param = getParamHelper(Names::Osc1_Pitch_Lfo2);
    auto& osc1PitchVelParam = getParamHelper(Names::Osc1_Pitch_Vel);
    auto& osc1PitchModParam = getParamHelper(Names::Osc1_Pitch_Mod);
    
    auto& osc2PitchEnv1Param = getParamHelper(Names::Osc2_Pitch_Env1);
    auto& osc2PitchEnv2Param = getParamHelper(Names::Osc2_Pitch_Env2);
    auto& osc2PitchLfo1Param = getParamHelper(Names::Osc2_Pitch_Lfo1);
    auto& osc2PitchLfo2Param = getParamHelper(Names::Osc2_Pitch_Lfo2);
    auto& osc2PitchVelParam = getParamHelper(Names::Osc2_Pitch_Vel);
    auto& osc2PitchModParam = getParamHelper(Names::Osc2_Pitch_Mod);
    
    auto& osc3PitchEnv1Param = getParamHelper(Names::Osc3_Pitch_Env1);
    auto& osc3PitchEnv2Param = getParamHelper(Names::Osc3_Pitch_Env2);
    auto& osc3PitchLfo1Param = getParamHelper(Names::Osc3_Pitch_Lfo1);
    auto& osc3PitchLfo2Param = getParamHelper(Names::Osc3_Pitch_Lfo2);
    auto& osc3PitchVelParam = getParamHelper(Names::Osc3_Pitch_Vel);
    auto& osc3PitchModParam = getParamHelper(Names::Osc3_Pitch_Mod);
    
    auto& cutoffEnv1Param = getParamHelper(Names::Cutoff_Env1);
    auto& cutoffEnv2Param = getParamHelper(Names::Cutoff_Env2);
    auto& cutoffLfo1Param = getParamHelper(Names::Cutoff_Lfo1);
    auto& cutoffLfo2Param = getParamHelper(Names::Cutoff_Lfo2);
    auto& cutoffVelParam = getParamHelper(Names::Cutoff_Vel);
    auto& cutoffModParam = getParamHelper(Names::Cutoff_Mod);
    
    auto& pwEnv1Param = getParamHelper(Names::PW_Env1);
    auto& pwEnv2Param = getParamHelper(Names::PW_Env2);
    auto& pwLfo1Param = getParamHelper(Names::PW_Lfo1);
    auto& pwLfo2Param = getParamHelper(Names::PW_Lfo2);
    auto& pwVelParam = getParamHelper(Names::PW_Vel);
    auto& pwModParam = getParamHelper(Names::PW_Mod);
    
    using LBS = LinearBarSlider;
    
    osc1PitchEnv1Slider = std::make_unique<LBS>(&osc1PitchEnv1Param, "Osc1 Pitch Env1");
    osc1PitchEnv2Slider = std::make_unique<LBS>(&osc1PitchEnv2Param, "Osc1 Pitch Env2");
    osc1PitchLfo1Slider = std::make_unique<LBS>(&osc1PitchLfo1Param, "Osc1 Pitch Lfo1");
    osc1PitchLfo2Slider = std::make_unique<LBS>(&osc1PitchLfo2Param, "Osc1 Pitch Lfo2");
    osc1PitchVelSlider = std::make_unique<LBS>(&osc1PitchVelParam, "Osc1 Pitch Vel");
    osc1PitchModSlider = std::make_unique<LBS>(&osc1PitchModParam, "Osc1 Pitch Mod");
    
    osc2PitchEnv1Slider = std::make_unique<LBS>(&osc2PitchEnv1Param, "Osc2 Pitch Env1");
    osc2PitchEnv2Slider = std::make_unique<LBS>(&osc2PitchEnv2Param, "Osc2 Pitch Env2");
    osc2PitchLfo1Slider = std::make_unique<LBS>(&osc2PitchLfo1Param, "Osc2 Pitch Lfo1");
    osc2PitchLfo2Slider = std::make_unique<LBS>(&osc2PitchLfo2Param, "Osc2 Pitch Lfo2");
    osc2PitchVelSlider = std::make_unique<LBS>(&osc2PitchVelParam, "Osc2 Pitch Vel");
    osc2PitchModSlider = std::make_unique<LBS>(&osc2PitchModParam, "Osc2 Pitch Mod");
    
    osc3PitchEnv1Slider = std::make_unique<LBS>(&osc3PitchEnv1Param, "Osc3 Pitch Env1");
    osc3PitchEnv2Slider = std::make_unique<LBS>(&osc3PitchEnv2Param, "Osc3 Pitch Env2");
    osc3PitchLfo1Slider = std::make_unique<LBS>(&osc3PitchLfo1Param, "Osc3 Pitch Lfo1");
    osc3PitchLfo2Slider = std::make_unique<LBS>(&osc3PitchLfo2Param, "Osc3 Pitch Lfo2");
    osc3PitchVelSlider = std::make_unique<LBS>(&osc3PitchVelParam, "Osc3 Pitch Vel");
    osc3PitchModSlider = std::make_unique<LBS>(&osc3PitchModParam, "Osc3 Pitch Mod");
    
    cutoffEnv1Slider = std::make_unique<LBS>(&cutoffEnv1Param, "Cutoff Env1");
    cutoffEnv2Slider = std::make_unique<LBS>(&cutoffEnv2Param, "Cutoff Env2");
    cutoffLfo1Slider = std::make_unique<LBS>(&cutoffLfo1Param, "Cutoff Lfo1");
    cutoffLfo2Slider = std::make_unique<LBS>(&cutoffLfo2Param, "Cutoff Lfo2");
    cutoffVelSlider = std::make_unique<LBS>(&cutoffVelParam, "Cutoff Vel");
    cutoffModSlider = std::make_unique<LBS>(&cutoffModParam, "Cutoff Mod");
    
    pwEnv1Slider = std::make_unique<LBS>(&pwEnv1Param, "PW Env1");
    pwEnv2Slider = std::make_unique<LBS>(&pwEnv2Param, "PW Env2");
    pwLfo1Slider = std::make_unique<LBS>(&pwLfo1Param, "PW Lfo1");
    pwLfo2Slider = std::make_unique<LBS>(&pwLfo2Param, "PW Lfo2");
    pwVelSlider = std::make_unique<LBS>(&pwVelParam, "PW Vel");
    pwModSlider = std::make_unique<LBS>(&pwModParam, "PW Mod");
    
    makeAttachmentHelper(osc1PitchEnv1SliderAttachment, Names::Osc1_Pitch_Env1, *osc1PitchEnv1Slider);
    makeAttachmentHelper(osc1PitchEnv2SliderAttachment, Names::Osc1_Pitch_Env2, *osc1PitchEnv2Slider);
    makeAttachmentHelper(osc1PitchLfo1SliderAttachment, Names::Osc1_Pitch_Lfo1, *osc1PitchLfo1Slider);
    makeAttachmentHelper(osc1PitchLfo1SliderAttachment, Names::Osc1_Pitch_Lfo1, *osc1PitchLfo1Slider);
    makeAttachmentHelper(osc1PitchVelSliderAttachment, Names::Osc1_Pitch_Vel, *osc1PitchVelSlider);
    makeAttachmentHelper(osc1PitchModSliderAttachment, Names::Osc1_Pitch_Mod, *osc1PitchModSlider);
    
    makeAttachmentHelper(osc2PitchEnv1SliderAttachment, Names::Osc2_Pitch_Env1, *osc2PitchEnv1Slider);
    makeAttachmentHelper(osc2PitchEnv2SliderAttachment, Names::Osc2_Pitch_Env2, *osc2PitchEnv2Slider);
    makeAttachmentHelper(osc2PitchLfo1SliderAttachment, Names::Osc2_Pitch_Lfo1, *osc2PitchLfo1Slider);
    makeAttachmentHelper(osc2PitchLfo1SliderAttachment, Names::Osc2_Pitch_Lfo1, *osc2PitchLfo1Slider);
    makeAttachmentHelper(osc2PitchVelSliderAttachment, Names::Osc2_Pitch_Vel, *osc2PitchVelSlider);
    makeAttachmentHelper(osc2PitchModSliderAttachment, Names::Osc2_Pitch_Mod, *osc2PitchModSlider);
    
    makeAttachmentHelper(osc3PitchEnv1SliderAttachment, Names::Osc3_Pitch_Env1, *osc3PitchEnv1Slider);
    makeAttachmentHelper(osc3PitchEnv2SliderAttachment, Names::Osc3_Pitch_Env2, *osc3PitchEnv2Slider);
    makeAttachmentHelper(osc3PitchLfo1SliderAttachment, Names::Osc3_Pitch_Lfo1, *osc3PitchLfo1Slider);
    makeAttachmentHelper(osc3PitchLfo1SliderAttachment, Names::Osc3_Pitch_Lfo1, *osc3PitchLfo1Slider);
    makeAttachmentHelper(osc3PitchVelSliderAttachment, Names::Osc3_Pitch_Vel, *osc3PitchVelSlider);
    makeAttachmentHelper(osc3PitchModSliderAttachment, Names::Osc3_Pitch_Mod, *osc3PitchModSlider);
    
    makeAttachmentHelper(cutoffEnv1SliderAttachment, Names::Cutoff_Env1, *cutoffEnv1Slider);
    makeAttachmentHelper(cutoffEnv2SliderAttachment, Names::Cutoff_Env2, *cutoffEnv2Slider);
    makeAttachmentHelper(cutoffLfo1SliderAttachment, Names::Cutoff_Lfo1, *cutoffLfo1Slider);
    makeAttachmentHelper(cutoffLfo2SliderAttachment, Names::Cutoff_Lfo2, *cutoffLfo2Slider);
    makeAttachmentHelper(cutoffVelSliderAttachment, Names::Cutoff_Vel, *cutoffVelSlider);
    makeAttachmentHelper(cutoffModSliderAttachment, Names::Cutoff_Mod, *cutoffModSlider);
    
    makeAttachmentHelper(pwEnv1SliderAttachment, Names::PW_Env1, *pwEnv1Slider);
    makeAttachmentHelper(pwEnv2SliderAttachment, Names::PW_Env2, *pwEnv2Slider);
    makeAttachmentHelper(pwLfo1SliderAttachment, Names::PW_Lfo1, *pwLfo1Slider);
    makeAttachmentHelper(pwLfo2SliderAttachment, Names::PW_Lfo2, *pwLfo2Slider);
    makeAttachmentHelper(pwVelSliderAttachment, Names::PW_Vel, *pwVelSlider);
    makeAttachmentHelper(pwModSliderAttachment, Names::PW_Mod, *pwModSlider);
    
    setSliderParams(*osc1PitchEnv1Slider);
    setSliderParams(*osc1PitchEnv2Slider);
    setSliderParams(*osc1PitchLfo1Slider);
    setSliderParams(*osc1PitchLfo2Slider);
    setSliderParams(*osc1PitchVelSlider);
    setSliderParams(*osc1PitchModSlider);
    
    setSliderParams(*osc2PitchEnv1Slider);
    setSliderParams(*osc2PitchEnv2Slider);
    setSliderParams(*osc2PitchLfo1Slider);
    setSliderParams(*osc2PitchLfo2Slider);
    setSliderParams(*osc2PitchVelSlider);
    setSliderParams(*osc2PitchModSlider);
    
    setSliderParams(*osc3PitchEnv1Slider);
    setSliderParams(*osc3PitchEnv2Slider);
    setSliderParams(*osc3PitchLfo1Slider);
    setSliderParams(*osc3PitchLfo2Slider);
    setSliderParams(*osc3PitchVelSlider);
    setSliderParams(*osc3PitchModSlider);
    
    setSliderParams(*cutoffEnv1Slider);
    setSliderParams(*cutoffEnv2Slider);
    setSliderParams(*cutoffLfo1Slider);
    setSliderParams(*cutoffLfo2Slider);
    setSliderParams(*cutoffVelSlider);
    setSliderParams(*cutoffModSlider);
    
    setSliderParams(*pwEnv1Slider);
    setSliderParams(*pwEnv2Slider);
    setSliderParams(*pwLfo1Slider);
    setSliderParams(*pwLfo2Slider);
    setSliderParams(*pwVelSlider);
    setSliderParams(*pwModSlider);
}

ModMatrixGUI::~ModMatrixGUI()
{
    setLookAndFeel(nullptr);
}

//void ModMatrix::paint(juce::Graphics &g)
//{
//    auto bounds = getLocalBounds();
//    
//    g.setColour(ColorScheme::getModuleBackgroundColor());
//    g.fillAll();
//    
//    NewSynth::drawModuleBackground(g, bounds);
//    
//    juce::Rectangle<int> componentArea (0, 0, getWidth(), getHeight());
//    juce::Rectangle<int> titleArea (0, 10, componentArea.getWidth(), lnf.LabelHeight);
//    g.drawRect(componentArea);
//    g.setFont(lnf.Header2Font);
//    g.drawText("Modulation", titleArea, juce::Justification::centredTop);
//}

int ModMatrixGUI::getNumRows()
{
    return numRows;
}

void ModMatrixGUI::paintRowBackground (juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    auto bounds = getLocalBounds();
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    NewSynth::drawModuleBackground(g, bounds);
}

void ModMatrixGUI::paintCell (juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (ColorScheme::getSliderFillColor());
    g.setFont (lnf.TextFont);
    
    g.fillRect (width - 1, 0, 1, height);
    g.fillRect (0, height - 1, width, 1);
    
    if(columnId == 1)
        g.fillRect(0, 0, 1, height);
    
    rowHeight = height;
}

void ModMatrixGUI::paint (juce::Graphics& g)
{
    const int fullWidth = getWidth() - 10;
    const int lbWidth = lnf.LabelWidth + 20;
    const int lbHeight = lnf.LabelHeight;
    const int rowY = 65;
    
    juce::Rectangle<int> componentArea (0, 0, getWidth(), getHeight());
    juce::Rectangle<int> titleArea (0, 10, fullWidth, lbHeight);
    juce::Rectangle<int> src1Area (5, rowY, lbWidth, lbHeight);
    juce::Rectangle<int> src2Area (5, rowY + rowHeight, lbWidth, lbHeight);
    juce::Rectangle<int> src3Area (5, rowY + rowHeight * 2, lbWidth, lbHeight);
    juce::Rectangle<int> src4Area (5, rowY + rowHeight * 3, lbWidth, lbHeight);
    juce::Rectangle<int> src5Area (5, rowY + rowHeight * 4, lbWidth, lbHeight);
    
    g.drawRect(componentArea);
    g.setFont(lnf.Header2Font);
    g.drawText("Modulation", titleArea, juce::Justification::centredTop);
    g.setFont(lnf.TextFont);
    g.setColour(juce::Colours::black);
    g.drawText ("Osc 1 Pitch", src1Area, juce::Justification::centredTop);
    g.drawText ("Osc 2 Pitch", src2Area, juce::Justification::centredTop);
    g.drawText ("Osc 3 Pitch", src3Area, juce::Justification::centredTop);
    g.drawText ("Filter Cutoff", src4Area, juce::Justification::centredTop);
    g.drawText ("Pulse width", src5Area, juce::Justification::centredTop);
}

void ModMatrixGUI::resized()
{
    using namespace juce;
    auto bounds = getLocalBounds().reduced(5);
    
    const int colHeight = 22;
    const int colY = 59;
    juce::Rectangle<int> tblArea (0, 0, getWidth(), getHeight());
    juce::Rectangle<int> row1Area (0, colY, getWidth(), colHeight);
    juce::Rectangle<int> row2Area (0, colY + colHeight, getWidth(), colHeight);
    juce::Rectangle<int> row3Area (0, colY + (colHeight * 2), getWidth(), colHeight);
    juce::Rectangle<int> row4Area (0, colY + (colHeight * 3), getWidth(), colHeight);
    juce::Rectangle<int> row5Area (0, colY + (colHeight * 4), getWidth(), colHeight);
    juce::Rectangle<int> row6Area (0, colY + (colHeight * 5), getWidth(), colHeight);
    juce::Rectangle<int> row7Area (0, colY + (colHeight * 6), getWidth(), colHeight);
    
    modMatrixTable.setBounds(tblArea.removeFromRight(colWidth * 6 + 10).withTrimmedRight(10).withTrimmedTop(30).withTrimmedBottom(1));
    
    auto spacer = FlexItem().withWidth(4);
    auto endCap = FlexItem().withWidth(6);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;
    
    row1.items.add(endCap);
    row1.items.add(FlexItem(*osc1PitchEnv1Slider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc1PitchEnv2Slider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc1PitchLfo1Slider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc1PitchLfo2Slider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc1PitchVelSlider).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(*osc1PitchModSlider).withFlex(1.f));
    row1.items.add(endCap);
    
    row1.performLayout(bounds);
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    row2.items.add(endCap);
    row2.items.add(FlexItem(*osc2PitchEnv1Slider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc2PitchEnv2Slider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc2PitchLfo1Slider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc2PitchLfo2Slider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc2PitchVelSlider).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(*osc2PitchModSlider).withFlex(1.f));
    row2.items.add(endCap);
    
    row2.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row3;
    row3.flexDirection = FlexBox::Direction::row;
    row3.flexWrap = FlexBox::Wrap::noWrap;
    
    row3.items.add(endCap);
    row3.items.add(FlexItem(*osc3PitchEnv1Slider).withFlex(1.f));
    row3.items.add(spacer);
    row3.items.add(FlexItem(*osc3PitchEnv2Slider).withFlex(1.f));
    row3.items.add(spacer);
    row3.items.add(FlexItem(*osc3PitchLfo1Slider).withFlex(1.f));
    row3.items.add(spacer);
    row3.items.add(FlexItem(*osc3PitchLfo2Slider).withFlex(1.f));
    row3.items.add(spacer);
    row3.items.add(FlexItem(*osc3PitchVelSlider).withFlex(1.f));
    row3.items.add(spacer);
    row3.items.add(FlexItem(*osc3PitchModSlider).withFlex(1.f));
    row3.items.add(endCap);
    
    row3.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row4;
    row4.flexDirection = FlexBox::Direction::row;
    row4.flexWrap = FlexBox::Wrap::noWrap;
    
    row4.items.add(endCap);
    row4.items.add(FlexItem(*cutoffEnv1Slider).withFlex(1.f));
    row4.items.add(spacer);
    row4.items.add(FlexItem(*cutoffEnv2Slider).withFlex(1.f));
    row4.items.add(spacer);
    row4.items.add(FlexItem(*cutoffLfo1Slider).withFlex(1.f));
    row4.items.add(spacer);
    row4.items.add(FlexItem(*cutoffLfo2Slider).withFlex(1.f));
    row4.items.add(spacer);
    row4.items.add(FlexItem(*cutoffVelSlider).withFlex(1.f));
    row4.items.add(spacer);
    row4.items.add(FlexItem(*cutoffModSlider).withFlex(1.f));
    row4.items.add(endCap);
    row4.items.add(endCap);
    
    row4.performLayout(bounds.withTrimmedTop(30));
    
    FlexBox row5;
    row5.flexDirection = FlexBox::Direction::row;
    row5.flexWrap = FlexBox::Wrap::noWrap;
    
    row5.items.add(endCap);
    row5.items.add(FlexItem(*pwEnv1Slider).withFlex(1.f));
    row5.items.add(spacer);
    row5.items.add(FlexItem(*pwEnv2Slider).withFlex(1.f));
    row5.items.add(spacer);
    row5.items.add(FlexItem(*pwLfo1Slider).withFlex(1.f));
    row5.items.add(spacer);
    row5.items.add(FlexItem(*pwLfo2Slider).withFlex(1.f));
    row5.items.add(spacer);
    row5.items.add(FlexItem(*pwVelSlider).withFlex(1.f));
    row5.items.add(spacer);
    row5.items.add(FlexItem(*pwModSlider).withFlex(1.f));
    row5.items.add(endCap);
    row5.items.add(endCap);
    
    row4.performLayout(bounds.withTrimmedTop(30));
    
//    osc1PitchModSlider->setBounds(row1Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
//    osc1PitchVelSlider->setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc1PitchLfo2Slider->setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc1PitchLfo1Slider->setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc1PitchEnv2Slider->setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc1PitchEnv1Slider->setBounds(row1Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
//    
//    osc2PitchModSlider->setBounds(row2Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
//    osc2PitchVelSlider->setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc2PitchLfo2Slider->setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc2PitchLfo1Slider->setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc2PitchEnv2Slider->setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc2PitchEnv1Slider->setBounds(row2Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
//    
//    osc3PitchModSlider->setBounds(row3Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
//    osc3PitchVelSlider->setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc3PitchLfo2Slider->setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc3PitchLfo1Slider->setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc3PitchEnv2Slider->setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    osc3PitchEnv1Slider->setBounds(row3Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
//    
//    cutoffModSlider->setBounds(row4Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
//    cutoffVelSlider->setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    cutoffLfo2Slider->setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    cutoffLfo1Slider->setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    cutoffEnv2Slider->setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    cutoffEnv1Slider->setBounds(row4Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
//    
//    pwModSlider->setBounds(row5Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
//    pwVelSlider->setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    pwLfo2Slider->setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    pwLfo1Slider->setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    pwEnv2Slider->setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
//    pwEnv1Slider->setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
}

void ModMatrixGUI::setSliderParams(LBS& slider){
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    addAndMakeVisible(slider);
}
