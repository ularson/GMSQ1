/*
  ==============================================================================

    ModMatrixGUI.h
    Created: 21 May 2024 22:31:00pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "../PluginProcessor.h"


//==============================================================================
/*
*/
class ModMatrixGUI : public juce::Component, public juce::TableListBoxModel
{
public:
    ModMatrixGUI(juce::AudioProcessorValueTreeState& apvts);
    ~ModMatrixGUI();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    void paintRowBackground (juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell (juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

private:
    LookAndFeel lnf;
    juce::TableListBox tblModMatrix;
    
    using Slider = juce::Slider;
    Slider osc1PitchEnv1Slider, osc1PitchEnv2Slider, osc1PitchLfo1Slider, osc1PitchLfo2Slider, osc1PitchVelSlider, osc1PitchModSlider;
    Slider osc2PitchEnv1Slider, osc2PitchEnv2Slider, osc2PitchLfo1Slider, osc2PitchLfo2Slider, osc2PitchVelSlider, osc2PitchModSlider;
    Slider osc3PitchEnv1Slider, osc3PitchEnv2Slider, osc3PitchLfo1Slider, osc3PitchLfo2Slider, osc3PitchVelSlider, osc3PitchModSlider;
    Slider cutoffEnv1Slider, cutoffEnv2Slider, cutoffLfo1Slider, cutoffLfo2Slider, cutoffVelSlider, cutoffModSlider;
    Slider PWEnv1Slider, PWEnv2Slider, PWLfo1Slider, PWLfo2Slider, PWVelSlider, PWModSlider;
    
    int colWidth = 40;
    int rowHeight;
    int numRows = 5;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> osc1PitchEnv1SliderAttachment, osc1PitchEnv2SliderAttachment, osc1PitchLfo1SliderAttachment, osc1PitchLfo2SliderAttachment, osc1PitchVelSliderAttachment, osc1PitchModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> osc2PitchEnv1SliderAttachment, osc2PitchEnv2SliderAttachment, osc2PitchLfo1SliderAttachment, osc2PitchLfo2SliderAttachment, osc2PitchVelSliderAttachment, osc2PitchModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> osc3PitchEnv1SliderAttachment, osc3PitchEnv2SliderAttachment, osc3PitchLfo1SliderAttachment, osc3PitchLfo2SliderAttachment, osc3PitchVelSliderAttachment, osc3PitchModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> cutoffEnv1SliderAttachment, cutoffEnv2SliderAttachment, cutoffLfo1SliderAttachment, cutoffLfo2SliderAttachment, cutoffVelSliderAttachment, cutoffModSliderAttachment;
    
    std::unique_ptr<SliderAttachment> pwEnv1SliderAttachment, pwEnv2SliderAttachment, pwLfo1SliderAttachment, pwLfo2SliderAttachment, pwVelSliderAttachment, pwModSliderAttachment;
    
    using Button = juce::ToggleButton;
    Button modEnabledButton;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> modEnabledButtonAttachment;
    
    void setSliderParams(juce::Slider& slider);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModMatrixGUI)
};
