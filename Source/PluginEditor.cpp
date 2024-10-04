/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GMSQ1AudioProcessorEditor::GMSQ1AudioProcessorEditor (GMSQ1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel(&lnf);
    
    addAndMakeVisible(osc1GUI);
    addAndMakeVisible(osc2GUI);
    addAndMakeVisible(osc3GUI);
    addAndMakeVisible(filterGUI);
    addAndMakeVisible(env1GUI);
    addAndMakeVisible(env2GUI);
    addAndMakeVisible(env3GUI);
    addAndMakeVisible(lfo1GUI);
    addAndMakeVisible(lfo2GUI);
    addAndMakeVisible(modMatrixGUI);
    addAndMakeVisible(masterGUI);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (720, 550);
}

GMSQ1AudioProcessorEditor::~GMSQ1AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void GMSQ1AudioProcessorEditor::paint (juce::Graphics& g)
{
    using namespace juce;
    
    g.fillAll(ColorScheme::getModuleBackgroundColor());
    
//    g.setFont(Font("Iosevka Term Slab", 30, 0)); //https://github.com/be5invis/Iosevka
//    
//    String title { "GM SQ1" };
//    g.setFont(20);
//    
//    auto bounds = getLocalBounds().withTrimmedTop(10);
//    
//    g.setColour(ColorScheme::getTextColor());
//    g.drawFittedText(title, bounds, juce::Justification::centredTop, 1);
}

void GMSQ1AudioProcessorEditor::resized()
{
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    using namespace juce;
    
    auto bounds = getLocalBounds().reduced(5); //.withTrimmedTop(40);
    auto spacer = FlexItem().withWidth(4);
    
    FlexBox row1;
    row1.flexDirection = FlexBox::Direction::row;
    row1.flexWrap = FlexBox::Wrap::noWrap;

    row1.items.add(spacer);
    row1.items.add(FlexItem(osc1GUI).withHeight(180).withWidth(180));
    row1.items.add(spacer);
    row1.items.add(FlexItem(osc2GUI).withHeight(180).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(osc3GUI).withHeight(180).withFlex(1.f));
    row1.items.add(spacer);
    row1.items.add(FlexItem(filterGUI).withHeight(180).withFlex(1.f));
    
    row1.performLayout(bounds);
    
    FlexBox row2;
    row2.flexDirection = FlexBox::Direction::row;
    row2.flexWrap = FlexBox::Wrap::noWrap;
    
    bounds = getLocalBounds().reduced(5).withTrimmedTop(180);
    
    row2.items.add(spacer);
    row2.items.add(FlexItem(env1GUI).withWidth(180).withHeight(180));
    row2.items.add(spacer);
    row2.items.add(FlexItem(env2GUI).withHeight(180).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(lfo1GUI).withHeight(180).withFlex(1.f));
    row2.items.add(spacer);
    row2.items.add(FlexItem(lfo2GUI).withHeight(180).withFlex(1.f));
    
    row2.performLayout(bounds);
    
    FlexBox row3;
    row3.flexDirection = FlexBox::Direction::row;
    row3.flexWrap = FlexBox::Wrap::noWrap;
    
    bounds = getLocalBounds().reduced(5).withTrimmedTop(360);
    
    row3.items.add(spacer);
    row3.items.add(FlexItem(modMatrixGUI).withWidth(356));
    row3.items.add(spacer);
    row3.items.add(FlexItem(env3GUI).withFlex(1.f));
    row3.items.add(spacer);
    row3.items.add(FlexItem(masterGUI).withFlex(1.f));
    
    row3.performLayout(bounds);
}
