/*
  ==============================================================================

    ModMatrix.h
    Created: 19 May 2024 10:20:18pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "LinearBarSlider.h"

struct ModMatrixGUI : juce::Component, juce::TableListBoxModel
{
    ModMatrixGUI(juce::AudioProcessorValueTreeState& apvts);
    ~ModMatrixGUI() override;
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    LookAndFeel lnf;
    juce::String label;
    juce::TableListBox modMatrixTable;
    
    int colWidth = 40;
    int rowHeight;
    int numRows = 5;
    
    using LBS = LinearBarSlider;
    std::unique_ptr<LBS> osc1PitchEnv1Slider, osc1PitchEnv2Slider, osc1PitchLfo1Slider, osc1PitchLfo2Slider, osc1PitchVelSlider, osc1PitchModSlider;
    std::unique_ptr<LBS> osc2PitchEnv1Slider, osc2PitchEnv2Slider, osc2PitchLfo1Slider, osc2PitchLfo2Slider, osc2PitchVelSlider, osc2PitchModSlider;
    std::unique_ptr<LBS> osc3PitchEnv1Slider, osc3PitchEnv2Slider, osc3PitchLfo1Slider, osc3PitchLfo2Slider, osc3PitchVelSlider, osc3PitchModSlider;
    std::unique_ptr<LBS> cutoffEnv1Slider, cutoffEnv2Slider, cutoffLfo1Slider, cutoffLfo2Slider, cutoffVelSlider, cutoffModSlider;
    std::unique_ptr<LBS> pwEnv1Slider, pwEnv2Slider, pwLfo1Slider, pwLfo2Slider, pwVelSlider, pwModSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> osc1PitchEnv1SliderAttachment, osc1PitchEnv2SliderAttachment, osc1PitchLfo1SliderAttachment, osc1PitchLfo2SliderAttachment, osc1PitchVelSliderAttachment, osc1PitchModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> osc2PitchEnv1SliderAttachment, osc2PitchEnv2SliderAttachment, osc2PitchLfo1SliderAttachment, osc2PitchLfo2SliderAttachment, osc2PitchVelSliderAttachment, osc2PitchModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> osc3PitchEnv1SliderAttachment, osc3PitchEnv2SliderAttachment, osc3PitchLfo1SliderAttachment, osc3PitchLfo2SliderAttachment, osc3PitchVelSliderAttachment, osc3PitchModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> cutoffEnv1SliderAttachment, cutoffEnv2SliderAttachment, cutoffLfo1SliderAttachment, cutoffLfo2SliderAttachment, cutoffVelSliderAttachment, cutoffModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> pwEnv1SliderAttachment, pwEnv2SliderAttachment, pwLfo1SliderAttachment, pwLfo2SliderAttachment, pwVelSliderAttachment, pwModSliderAttachment;
    
    void setSliderParams(LBS& slider);
    int getNumRows() override;
    void paintRowBackground (juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell (juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
};
