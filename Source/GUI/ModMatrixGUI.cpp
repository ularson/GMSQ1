/*
  ==============================================================================

    ModMatrixGUI.cpp
    Created: 21 May 2024 22:31:00pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModMatrixGUI.h"
#include "../DSP/Params.h"

//==============================================================================
ModMatrixGUI::ModMatrixGUI(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    setLookAndFeel(&lnf);
    
    tblModMatrix.setModel(this);
    tblModMatrix.autoSizeAllColumns();
    tblModMatrix.getViewport()->setScrollBarsShown(true, false);
    tblModMatrix.getHeader().addColumn("Env 1", 1, colWidth);
    tblModMatrix.getHeader().addColumn("Env 2", 2, colWidth);
    tblModMatrix.getHeader().addColumn("Lfo 1", 3, colWidth);
    tblModMatrix.getHeader().addColumn("Lfo 2", 4, colWidth);
    tblModMatrix.getHeader().addColumn("Vel", 5, colWidth);
    tblModMatrix.getHeader().addColumn("Mod", 6, colWidth);
    addAndMakeVisible(&tblModMatrix);
    
    setSliderParams(osc1PitchEnv1Slider);
    setSliderParams(osc1PitchEnv2Slider);
    setSliderParams(osc1PitchLfo1Slider);
    setSliderParams(osc1PitchLfo2Slider);
    setSliderParams(osc1PitchVelSlider);
    setSliderParams(osc1PitchModSlider);
    
    setSliderParams(osc2PitchEnv1Slider);
    setSliderParams(osc2PitchEnv2Slider);
    setSliderParams(osc2PitchLfo1Slider);
    setSliderParams(osc2PitchLfo2Slider);
    setSliderParams(osc2PitchVelSlider);
    setSliderParams(osc2PitchModSlider);
    
    setSliderParams(osc3PitchEnv1Slider);
    setSliderParams(osc3PitchEnv2Slider);
    setSliderParams(osc3PitchLfo1Slider);
    setSliderParams(osc3PitchLfo2Slider);
    setSliderParams(osc3PitchVelSlider);
    setSliderParams(osc3PitchModSlider);
    
    setSliderParams(cutoffEnv1Slider);
    setSliderParams(cutoffEnv2Slider);
    setSliderParams(cutoffLfo1Slider);
    setSliderParams(cutoffLfo2Slider);
    setSliderParams(cutoffVelSlider);
    setSliderParams(cutoffModSlider);
    
    setSliderParams(PWEnv1Slider);
    setSliderParams(PWEnv2Slider);
    setSliderParams(PWLfo1Slider);
    setSliderParams(PWLfo2Slider);
    setSliderParams(PWVelSlider);
    setSliderParams(PWModSlider);
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider)
    {
        GMSQ1::makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(osc1PitchEnv1SliderAttachment, Names::Osc1_Pitch_Env1, osc1PitchEnv1Slider);
    makeAttachmentHelper(osc1PitchEnv2SliderAttachment, Names::Osc1_Pitch_Env2, osc1PitchEnv2Slider);
    makeAttachmentHelper(osc1PitchLfo1SliderAttachment, Names::Osc1_Pitch_Lfo1, osc1PitchLfo1Slider);
    makeAttachmentHelper(osc1PitchLfo2SliderAttachment, Names::Osc1_Pitch_Lfo2, osc1PitchLfo2Slider);
    makeAttachmentHelper(osc1PitchVelSliderAttachment, Names::Osc1_Pitch_Vel, osc1PitchVelSlider);
    makeAttachmentHelper(osc1PitchModSliderAttachment, Names::Osc1_Pitch_Mod, osc1PitchModSlider);
    
    makeAttachmentHelper(osc2PitchEnv1SliderAttachment, Names::Osc2_Pitch_Env1, osc2PitchEnv1Slider);
    makeAttachmentHelper(osc2PitchEnv2SliderAttachment, Names::Osc2_Pitch_Env2, osc2PitchEnv2Slider);
    makeAttachmentHelper(osc2PitchLfo1SliderAttachment, Names::Osc2_Pitch_Lfo1, osc2PitchLfo1Slider);
    makeAttachmentHelper(osc2PitchLfo2SliderAttachment, Names::Osc2_Pitch_Lfo2, osc2PitchLfo2Slider);
    makeAttachmentHelper(osc2PitchVelSliderAttachment, Names::Osc2_Pitch_Vel, osc2PitchVelSlider);
    makeAttachmentHelper(osc2PitchModSliderAttachment, Names::Osc2_Pitch_Mod, osc2PitchModSlider);
    
    makeAttachmentHelper(osc3PitchEnv1SliderAttachment, Names::Osc3_Pitch_Env1, osc3PitchEnv1Slider);
    makeAttachmentHelper(osc3PitchEnv2SliderAttachment, Names::Osc3_Pitch_Env2, osc3PitchEnv2Slider);
    makeAttachmentHelper(osc3PitchLfo1SliderAttachment, Names::Osc3_Pitch_Lfo1, osc3PitchLfo1Slider);
    makeAttachmentHelper(osc3PitchLfo2SliderAttachment, Names::Osc3_Pitch_Lfo2, osc3PitchLfo2Slider);
    makeAttachmentHelper(osc3PitchVelSliderAttachment, Names::Osc3_Pitch_Vel, osc3PitchVelSlider);
    makeAttachmentHelper(osc3PitchModSliderAttachment, Names::Osc3_Pitch_Mod, osc3PitchModSlider);
    
    makeAttachmentHelper(cutoffEnv1SliderAttachment, Names::Cutoff_Env1, cutoffEnv1Slider);
    makeAttachmentHelper(cutoffEnv2SliderAttachment, Names::Cutoff_Env2, cutoffEnv2Slider);
    makeAttachmentHelper(cutoffLfo1SliderAttachment, Names::Cutoff_Lfo1, cutoffLfo1Slider);
    makeAttachmentHelper(cutoffLfo2SliderAttachment, Names::Cutoff_Lfo2, cutoffLfo2Slider);
    makeAttachmentHelper(cutoffVelSliderAttachment, Names::Cutoff_Vel, cutoffVelSlider);
    makeAttachmentHelper(cutoffModSliderAttachment, Names::Cutoff_Mod, cutoffModSlider);
    
    makeAttachmentHelper(pwEnv1SliderAttachment, Names::PW_Env1, PWEnv1Slider);
    makeAttachmentHelper(pwEnv2SliderAttachment, Names::PW_Env2, PWEnv2Slider);
    makeAttachmentHelper(pwLfo1SliderAttachment, Names::PW_Lfo1, PWLfo1Slider);
    makeAttachmentHelper(pwLfo2SliderAttachment, Names::PW_Lfo2, PWLfo2Slider);
    makeAttachmentHelper(pwVelSliderAttachment, Names::PW_Vel, PWVelSlider);
    makeAttachmentHelper(pwModSliderAttachment, Names::PW_Mod, PWModSlider);
    
    makeAttachmentHelper(modEnabledButtonAttachment,
                         Names::Mod_Enabled,
                         modEnabledButton);
    
    addAndMakeVisible(modEnabledButton);
}


ModMatrixGUI::~ModMatrixGUI()
{
    setLookAndFeel(nullptr);
}

int ModMatrixGUI::getNumRows()
{
    return numRows;
}

void ModMatrixGUI::paintRowBackground (juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    g.fillAll (ColorScheme::getModuleBackgroundColor());
}

void ModMatrixGUI::paintCell (juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (ColorScheme::getTextColor());
    g.setFont (lnf.TextFont);
    
    g.fillRect (width - 1, 0, 1, height);
    g.fillRect (0, height - 1, width, 1);
    
    if(columnId == 1)
        g.fillRect(0, 0, 1, height);
    
    rowHeight = height;
}

void ModMatrixGUI::paint (juce::Graphics& g)
{
    using namespace juce;
    
    auto bounds = getLocalBounds();
    const int lbWidth = lnf.LabelWidth + 80;
    const int lbHeight = lnf.LabelHeight;
    const int rowY = 65;
    
    g.setColour(ColorScheme::getModuleBackgroundColor());
    g.fillAll();
    
    GMSQ1::drawModuleBackground(g, bounds);
    
    juce::Rectangle<int> componentArea (0, 0, getWidth(), getHeight());
    juce::Rectangle<int> titleArea (5, 10, getWidth(), lbHeight);
    juce::Rectangle<int> src1Area (5, rowY, lbWidth, lbHeight);
    juce::Rectangle<int> src2Area (5, rowY + rowHeight, lbWidth, lbHeight);
    juce::Rectangle<int> src3Area (5, rowY + rowHeight * 2, lbWidth, lbHeight);
    juce::Rectangle<int> src4Area (5, rowY + rowHeight * 3, lbWidth, lbHeight);
    juce::Rectangle<int> src5Area (5, rowY + rowHeight * 4, lbWidth, lbHeight);
    
    g.drawRect(componentArea);
    g.setFont(lnf.TextFont);
    g.setColour(Colours::black);
    g.drawText("Modulation", titleArea, Justification::centredTop);
    
    modEnabledButton.setBounds(componentArea.removeFromTop(60).withTrimmedLeft(10));
    
    g.drawText ("Osc 1 Pitch", src1Area, Justification::centredTop);
    g.drawText ("Osc 2 Pitch", src2Area, Justification::centredTop);
    g.drawText ("Osc 3 Pitch", src3Area, Justification::centredTop);
    g.drawText ("Filter Cutoff", src4Area, Justification::centredTop);
    g.drawText ("Pulse width", src5Area, Justification::centredTop);
}

void ModMatrixGUI::resized()
{
    const int colHeight = 22;
    const int colY = 62;
    juce::Rectangle<int> tblArea (0, 0, getWidth(), getHeight());
    juce::Rectangle<int> row1Area (0, colY, getWidth(), colHeight);
    juce::Rectangle<int> row2Area (0, colY + colHeight, getWidth(), colHeight);
    juce::Rectangle<int> row3Area (0, colY + (colHeight * 2), getWidth(), colHeight);
    juce::Rectangle<int> row4Area (0, colY + (colHeight * 3), getWidth(), colHeight);
    juce::Rectangle<int> row5Area (0, colY + (colHeight * 4), getWidth(), colHeight);
    juce::Rectangle<int> row6Area (0, colY + (colHeight * 5), getWidth(), colHeight);
    juce::Rectangle<int> row7Area (0, colY + (colHeight * 6), getWidth(), colHeight);
    
    tblModMatrix.setBounds(tblArea.removeFromRight(colWidth * 6 + 10).withTrimmedRight(10).withTrimmedTop(35).withTrimmedBottom(7));
    
    osc1PitchModSlider.setBounds(row1Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
    osc1PitchVelSlider.setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc1PitchLfo2Slider.setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc1PitchLfo1Slider.setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc1PitchEnv2Slider.setBounds(row1Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc1PitchEnv1Slider.setBounds(row1Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
    
    osc2PitchModSlider.setBounds(row2Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
    osc2PitchVelSlider.setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc2PitchLfo2Slider.setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc2PitchLfo1Slider.setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc2PitchEnv2Slider.setBounds(row2Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc2PitchEnv1Slider.setBounds(row2Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
    
    osc3PitchModSlider.setBounds(row3Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
    osc3PitchVelSlider.setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc3PitchLfo2Slider.setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc3PitchLfo1Slider.setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc3PitchEnv2Slider.setBounds(row3Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    osc3PitchEnv1Slider.setBounds(row3Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
    
    cutoffModSlider.setBounds(row4Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
    cutoffVelSlider.setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    cutoffLfo2Slider.setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    cutoffLfo1Slider.setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    cutoffEnv2Slider.setBounds(row4Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    cutoffEnv1Slider.setBounds(row4Area.removeFromRight(colWidth).withTrimmedLeft(1).withTrimmedRight(1).withTrimmedBottom(1));
    
    PWModSlider.setBounds(row5Area.removeFromRight(colWidth + 10).withTrimmedRight(11).withTrimmedBottom(1));
    PWVelSlider.setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    PWLfo2Slider.setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    PWLfo1Slider.setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    PWEnv2Slider.setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
    PWEnv1Slider.setBounds(row5Area.removeFromRight(colWidth).withTrimmedRight(1).withTrimmedBottom(1));
}

void ModMatrixGUI::setSliderParams(juce::Slider& slider){
    slider.setSliderStyle(Slider::SliderStyle::LinearBar);
    addAndMakeVisible(slider);
}

