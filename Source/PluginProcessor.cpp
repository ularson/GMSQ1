/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DSP/Params.h"

//==============================================================================
GMSQ1AudioProcessor::GMSQ1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    for (int i = 0; i < Const::NR_OF_VOICES; i++)
    {
        synth.addVoice (new SynthVoice());
    }
    
    synth.addSound(new SynthSound());
}

GMSQ1AudioProcessor::~GMSQ1AudioProcessor()
{
}

//==============================================================================
const juce::String GMSQ1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GMSQ1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GMSQ1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GMSQ1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GMSQ1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GMSQ1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GMSQ1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GMSQ1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GMSQ1AudioProcessor::getProgramName (int index)
{
    return {};
}

void GMSQ1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void GMSQ1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GMSQ1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
void GMSQ1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++) {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

//==============================================================================
void GMSQ1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    setParams();
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool GMSQ1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GMSQ1AudioProcessor::createEditor()
{
    //return new juce::GenericAudioProcessorEditor (*this);
    return new GMSQ1AudioProcessorEditor (*this);
}

//==============================================================================
void GMSQ1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void GMSQ1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if(tree.isValid())
    {
        apvts.replaceState(tree);
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout GMSQ1AudioProcessor::createParameterLayout()
{
    using namespace juce;
    using namespace Params;
    const auto& params = GetParams();
    AudioProcessorValueTreeState::ParameterLayout layout;
    
    const StringArray waveRange = {"Sine", "Saw", "Square", "Triangle", "Pulse", "Noise" };
    const StringArray filterModeRange = {"LP24", "LP12", "BP24", "BP12", "HP24", "HP12" };
    const StringArray lfoWaveRange = {"Sine", "Saw", "Square", "Triangle" };
    const StringArray lfoSourceRange = {"None", "Mod" };
    const StringArray lfoDestRange = {"Pitch", "Cutoff", "PW" };
    auto zeroToHundredRange = NormalisableRange<float>(0, 100, 1, 1);
    auto oneToHundredRange = NormalisableRange<float>(1, 100, 1, 1);
    auto lfoRateRange = NormalisableRange<float>(0.f, 10.f, .1f, 1);
    auto semiRange = NormalisableRange<float>(-48, 48, 1, 1);
    auto centsRange = NormalisableRange<float>(-50, 50, 1, 1); // Not working!
    auto pwRange = NormalisableRange<float>(-3.0f, 3.0f, 0.1f, 1);

    
    // Osc 1
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::Osc1_Wave), 1),
                                                      params.at(Names::Osc1_Wave),
                                                      waveRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Semitones), 1),
                                                     params.at(Names::Osc1_Semitones),
                                                     semiRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Cents), 1),
                                                     params.at(Names::Osc1_Cents),
                                                     centsRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Level), 1),
                                                     params.at(Names::Osc1_Level),
                                                     zeroToHundredRange,
                                                     100));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_PW), 1),
                                                     params.at(Names::Osc1_PW),
                                                     pwRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Sync), 1),
                                                     params.at(Names::Osc1_Sync),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::Osc1_Enabled), 1),
                                                    params.at(Names::Osc1_Enabled),
                                                    true));
    
    // Osc 2
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::Osc2_Wave), 1),
                                                      params.at(Names::Osc2_Wave),
                                                      waveRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Semitones), 1),
                                                     params.at(Names::Osc2_Semitones),
                                                     semiRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Cents), 1),
                                                     params.at(Names::Osc2_Cents),
                                                     centsRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Level), 1),
                                                     params.at(Names::Osc2_Level),
                                                     zeroToHundredRange,
                                                     100));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_PW), 1),
                                                     params.at(Names::Osc2_PW),
                                                     pwRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_FM), 1),
                                                     params.at(Names::Osc2_FM),
                                                     pwRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::Osc2_Enabled), 1),
                                                    params.at(Names::Osc2_Enabled),
                                                    true));
    
    // Osc 3
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::Osc3_Wave), 1),
                                                      params.at(Names::Osc3_Wave),
                                                      waveRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Semitones), 1),
                                                     params.at(Names::Osc3_Semitones),
                                                     semiRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Cents), 1),
                                                     params.at(Names::Osc3_Cents),
                                                     centsRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Level), 1),
                                                     params.at(Names::Osc3_Level),
                                                     zeroToHundredRange,
                                                     100));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_PW), 1),
                                                     params.at(Names::Osc3_PW),
                                                     pwRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::Osc3_Enabled), 1),
                                                    params.at(Names::Osc3_Enabled),
                                                    true));
    
    // Filter
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::Filter_Mode), 1),
                                                      params.at(Names::Filter_Mode),
                                                      filterModeRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Filter_Cutoff), 1),
                                                     params.at(Names::Filter_Cutoff),
                                                     NormalisableRange<float>(Const::MIN_FREQUENCY, Const::MAX_FREQUENCY, 1.f, 1),
                                                     Const::MAX_FREQUENCY));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Filter_Res), 1),
                                                     params.at(Names::Filter_Res),
                                                     NormalisableRange<float>(.0f, 1.0f, .1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Filter_Vel), 1),
                                                     params.at(Names::Filter_Vel),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Filter_Env), 1),
                                                     params.at(Names::Filter_Env),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Filter_Key), 1),
                                                     params.at(Names::Filter_Key),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::Filter_Enabled), 1),
                                                    params.at(Names::Filter_Enabled),
                                                    true));
    
    // Env1
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV1_Attack), 1),
                                                     params.at(Names::ENV1_Attack),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV1_Decay), 1),
                                                     params.at(Names::ENV1_Decay),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV1_Sustain), 1),
                                                     params.at(Names::ENV1_Sustain),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     .5f));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV1_Release), 1),
                                                     params.at(Names::ENV1_Release),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV1_Key), 1),
                                                     params.at(Names::ENV1_Key),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV1_Vel), 1),
                                                     params.at(Names::ENV1_Vel),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::ENV1_Enabled), 1),
                                                    params.at(Names::ENV1_Enabled),
                                                    true));
    
    // Env2
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV2_Attack), 1),
                                                     params.at(Names::ENV2_Attack),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV2_Decay), 1),
                                                     params.at(Names::ENV2_Decay),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV2_Sustain), 1),
                                                     params.at(Names::ENV2_Sustain),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     .5f));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV2_Release), 1),
                                                     params.at(Names::ENV2_Release),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV2_Key), 1),
                                                     params.at(Names::ENV2_Key),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV2_Vel), 1),
                                                     params.at(Names::ENV2_Vel),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::ENV2_Enabled), 1),
                                                    params.at(Names::ENV2_Enabled),
                                                    true));
    
    // Env3
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV3_Attack), 1),
                                                     params.at(Names::ENV3_Attack),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV3_Decay), 1),
                                                     params.at(Names::ENV3_Decay),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV3_Sustain), 1),
                                                     params.at(Names::ENV3_Sustain),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     .5f));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV3_Release), 1),
                                                     params.at(Names::ENV3_Release),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV3_Key), 1),
                                                     params.at(Names::ENV3_Key),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::ENV3_Vel), 1),
                                                     params.at(Names::ENV3_Vel),
                                                     NormalisableRange<float>(0, 1, 0.1f, 1),
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::ENV3_Enabled), 1),
                                                    params.at(Names::ENV3_Enabled),
                                                    true));
    
    // LFO1
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::LFO1_Source), 1),
                                                      params.at(Names::LFO1_Source),
                                                      lfoSourceRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::LFO1_Dest), 1),
                                                      params.at(Names::LFO1_Dest),
                                                      lfoDestRange,
                                                      0));
    
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::LFO1_Wave), 1),
                                                      params.at(Names::LFO1_Wave),
                                                      lfoWaveRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::LFO1_Rate), 1),
                                                     params.at(Names::LFO1_Rate),
                                                     lfoRateRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::LFO1_Gain), 1),
                                                     params.at(Names::LFO1_Gain),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::LFO1_Reset), 1),
                                                    params.at(Names::LFO1_Reset),
                                                    false));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::LFO1_Enabled), 1),
                                                    params.at(Names::LFO1_Enabled),
                                                    true));
    
    // LFO2
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::LFO2_Source), 1),
                                                      params.at(Names::LFO2_Source),
                                                      lfoSourceRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::LFO2_Dest), 1),
                                                      params.at(Names::LFO2_Dest),
                                                      lfoDestRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID(params.at(Names::LFO2_Wave), 1),
                                                      params.at(Names::LFO2_Wave),
                                                      lfoWaveRange,
                                                      0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::LFO2_Rate), 1),
                                                     params.at(Names::LFO2_Rate),
                                                     lfoRateRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::LFO2_Gain), 1),
                                                     params.at(Names::LFO2_Gain),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::LFO2_Reset), 1),
                                                    params.at(Names::LFO2_Reset),
                                                    false));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::LFO2_Enabled), 1),
                                                    params.at(Names::LFO2_Enabled),
                                                    true));
    
    // Modulation
    
    //Osc 1 mod
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Pitch_Env1), 1),
                                                     params.at(Names::Osc1_Pitch_Env1),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Pitch_Env2), 1),
                                                     params.at(Names::Osc1_Pitch_Env2),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Pitch_Lfo1), 1),
                                                     params.at(Names::Osc1_Pitch_Lfo1),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Pitch_Lfo2), 1),
                                                     params.at(Names::Osc1_Pitch_Lfo2),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Pitch_Vel), 1),
                                                     params.at(Names::Osc1_Pitch_Vel),
                                                     zeroToHundredRange,
                                                     0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc1_Pitch_Mod), 1),
                                                   params.at(Names::Osc1_Pitch_Mod),
                                                   zeroToHundredRange,
                                                   0));
    
    //Osc 2 mod
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Pitch_Env1), 1),
                                                   params.at(Names::Osc2_Pitch_Env1),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Pitch_Env2), 1),
                                                   params.at(Names::Osc2_Pitch_Env2),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Pitch_Lfo1), 1),
                                                   params.at(Names::Osc2_Pitch_Lfo1),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Pitch_Lfo2), 1),
                                                   params.at(Names::Osc2_Pitch_Lfo2),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Pitch_Vel), 1),
                                                   params.at(Names::Osc2_Pitch_Vel),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc2_Pitch_Mod), 1),
                                                   params.at(Names::Osc2_Pitch_Mod),
                                                   zeroToHundredRange,
                                                   0));
    
    //Osc 3 mod
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Pitch_Env1), 1),
                                                   params.at(Names::Osc3_Pitch_Env1),
                                                   zeroToHundredRange,
                                                   0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Pitch_Env2), 1),
                                                   params.at(Names::Osc3_Pitch_Env2),
                                                   zeroToHundredRange,
                                                   0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Pitch_Lfo1), 1),
                                                   params.at(Names::Osc3_Pitch_Lfo1),
                                                   zeroToHundredRange,
                                                   0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Pitch_Lfo2), 1),
                                                   params.at(Names::Osc3_Pitch_Lfo2),
                                                   zeroToHundredRange,
                                                   0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Pitch_Vel), 1),
                                                   params.at(Names::Osc3_Pitch_Vel),
                                                   zeroToHundredRange,
                                                   0));
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Osc3_Pitch_Mod), 1),
                                                   params.at(Names::Osc3_Pitch_Mod),
                                                   zeroToHundredRange,
                                                   0));

    //Filter mod
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Cutoff_Env1), 1),
                                                   params.at(Names::Cutoff_Env1),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Cutoff_Env2), 1),
                                                   params.at(Names::Cutoff_Env2),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Cutoff_Lfo1), 1),
                                                   params.at(Names::Cutoff_Lfo1),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Cutoff_Lfo2), 1),
                                                   params.at(Names::Cutoff_Lfo2),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Cutoff_Vel), 1),
                                                   params.at(Names::Cutoff_Vel),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Cutoff_Mod), 1),
                                                   params.at(Names::Cutoff_Mod),
                                                   zeroToHundredRange,
                                                   0));
    
    // PW mod
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::PW_Env1), 1),
                                                   params.at(Names::PW_Env1),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::PW_Env2), 1),
                                                   params.at(Names::PW_Env2),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::PW_Lfo1), 1),
                                                   params.at(Names::PW_Lfo1),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::PW_Lfo2), 1),
                                                   params.at(Names::PW_Lfo2),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::PW_Vel), 1),
                                                   params.at(Names::PW_Vel),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::PW_Mod), 1),
                                                   params.at(Names::PW_Mod),
                                                   zeroToHundredRange,
                                                   0));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::Mod_Enabled), 1),
                                                    params.at(Names::Mod_Enabled),
                                                    true));
    
    // Master
    
    auto gainRange = NormalisableRange<float>(.0f, 1.0f, .01f, 0.5f);
    auto pitchBendRange = NormalisableRange<float>(0, 48, 1, 1);
    auto voicesRange = NormalisableRange<float>(0, 32, 1, 1);
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Master_Gain), 1),
                                                     params.at(Names::Master_Gain),
                                                     gainRange,
                                                     .5f));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Pitch_Bend), 1),
                                                     params.at(Names::Pitch_Bend),
                                                     pitchBendRange,
                                                     2));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID(params.at(Names::Nr_Of_Voices), 1),
                                                     params.at(Names::Nr_Of_Voices),
                                                     voicesRange,
                                                     16));
    
    layout.add(std::make_unique<AudioParameterBool>(juce::ParameterID(params.at(Names::Master_Enabled), 1),
                                                    params.at(Names::Master_Enabled),
                                                    true));
    
    return layout;
}

void GMSQ1AudioProcessor::setParams()
{
    using namespace Params;
    const auto& params = GetParams();
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& osc1Wave = *apvts.getRawParameterValue (params.at(Names::Osc1_Wave));
            auto& osc1Semitones = *apvts.getRawParameterValue (params.at(Names::Osc1_Semitones));
            auto& osc1Cents = *apvts.getRawParameterValue (params.at(Names::Osc1_Cents));
            auto& osc1Level = *apvts.getRawParameterValue (params.at(Names::Osc1_Level));
            auto& osc1PulseWidth = *apvts.getRawParameterValue (params.at(Names::Osc1_PW));
            auto& osc1Sync = *apvts.getRawParameterValue (params.at(Names::Osc1_Sync));
            auto& osc1Enabled = *apvts.getRawParameterValue (params.at(Names::Osc1_Enabled));
            
            auto& osc2Wave = *apvts.getRawParameterValue (params.at(Names::Osc2_Wave));
            auto& osc2Semitones = *apvts.getRawParameterValue (params.at(Names::Osc2_Semitones));
            auto& osc2Cents = *apvts.getRawParameterValue (params.at(Names::Osc2_Cents));
            auto& osc2Level = *apvts.getRawParameterValue (params.at(Names::Osc2_Level));
            auto& osc2PulseWidth = *apvts.getRawParameterValue (params.at(Names::Osc2_PW));
            auto& osc2FM = *apvts.getRawParameterValue (params.at(Names::Osc2_FM));
            auto& osc2Enabled = *apvts.getRawParameterValue (params.at(Names::Osc2_Enabled));
            
            auto& osc3Wave = *apvts.getRawParameterValue (params.at(Names::Osc3_Wave));
            auto& osc3Semitones = *apvts.getRawParameterValue (params.at(Names::Osc3_Semitones));
            auto& osc3Cents = *apvts.getRawParameterValue (params.at(Names::Osc3_Cents));
            auto& osc3Level = *apvts.getRawParameterValue (params.at(Names::Osc3_Level));
            auto& osc3PulseWidth = *apvts.getRawParameterValue (params.at(Names::Osc3_PW));
            auto& osc3Enabled = *apvts.getRawParameterValue (params.at(Names::Osc3_Enabled));
            
            auto& env1Attack = *apvts.getRawParameterValue (params.at(Names::ENV1_Attack));
            auto& env1Decay = *apvts.getRawParameterValue (params.at(Names::ENV1_Decay));
            auto& env1Sustain = *apvts.getRawParameterValue (params.at(Names::ENV1_Sustain));
            auto& env1Release = *apvts.getRawParameterValue (params.at(Names::ENV1_Release));
            auto& env1Key = *apvts.getRawParameterValue (params.at(Names::ENV1_Key));
            auto& env1Vel = *apvts.getRawParameterValue (params.at(Names::ENV1_Vel));
            auto& env1Enabled = *apvts.getRawParameterValue (params.at(Names::ENV1_Enabled));
            
            auto& env2Attack = *apvts.getRawParameterValue (params.at(Names::ENV2_Attack));
            auto& env2Decay = *apvts.getRawParameterValue (params.at(Names::ENV2_Decay));
            auto& env2Sustain = *apvts.getRawParameterValue (params.at(Names::ENV2_Sustain));
            auto& env2Release = *apvts.getRawParameterValue (params.at(Names::ENV2_Release));
            auto& env2Key = *apvts.getRawParameterValue (params.at(Names::ENV2_Key));
            auto& env2Vel = *apvts.getRawParameterValue (params.at(Names::ENV2_Vel));
            auto& env2Enabled = *apvts.getRawParameterValue (params.at(Names::ENV2_Enabled));
            
            auto& env3Attack = *apvts.getRawParameterValue (params.at(Names::ENV3_Attack));
            auto& env3Decay = *apvts.getRawParameterValue (params.at(Names::ENV3_Decay));
            auto& env3Sustain = *apvts.getRawParameterValue (params.at(Names::ENV3_Sustain));
            auto& env3Release = *apvts.getRawParameterValue (params.at(Names::ENV3_Release));
            auto& env3Key = *apvts.getRawParameterValue (params.at(Names::ENV3_Key));
            auto& env3Vel = *apvts.getRawParameterValue (params.at(Names::ENV3_Vel));
            auto& env3Enabled = *apvts.getRawParameterValue (params.at(Names::ENV3_Enabled));
            
            auto& filterMode = *apvts.getRawParameterValue (params.at(Names::Filter_Mode));
            auto& filterCutoff = *apvts.getRawParameterValue (params.at(Names::Filter_Cutoff));
            auto& filterResonance = *apvts.getRawParameterValue (params.at(Names::Filter_Res));
            auto& filterVel = *apvts.getRawParameterValue (params.at(Names::Filter_Vel));
            auto& filterEnv = *apvts.getRawParameterValue (params.at(Names::Filter_Env));
            auto& filterKey = *apvts.getRawParameterValue (params.at(Names::Filter_Key));
            auto& filterEnabled = *apvts.getRawParameterValue (params.at(Names::Filter_Enabled));
            
            auto& lfo1Source = *apvts.getRawParameterValue (params.at(Names::LFO1_Source));
            auto& lfo1Destination = *apvts.getRawParameterValue (params.at(Names::LFO1_Dest));
            auto& lfo1Wave = *apvts.getRawParameterValue (params.at(Names::LFO1_Wave));
            auto& lfo1Rate = *apvts.getRawParameterValue (params.at(Names::LFO1_Rate));
            auto& lfo1Gain = *apvts.getRawParameterValue (params.at(Names::LFO1_Gain));
            auto& lfo1Reset = *apvts.getRawParameterValue (params.at(Names::LFO1_Reset));
            auto& lfo1Enabled = *apvts.getRawParameterValue (params.at(Names::LFO1_Enabled));
            
            auto& lfo2Source = *apvts.getRawParameterValue (params.at(Names::LFO2_Source));
            auto& lfo2Destination = *apvts.getRawParameterValue (params.at(Names::LFO2_Dest));
            auto& lfo2Wave = *apvts.getRawParameterValue (params.at(Names::LFO2_Wave));
            auto& lfo2Rate = *apvts.getRawParameterValue (params.at(Names::LFO2_Rate));
            auto& lfo2Gain = *apvts.getRawParameterValue (params.at(Names::LFO2_Gain));
            auto& lfo2Reset = *apvts.getRawParameterValue (params.at(Names::LFO2_Reset));
            auto& lfo2Enabled = *apvts.getRawParameterValue (params.at(Names::LFO2_Enabled));
            
            auto& osc1PitchEnv1 = *apvts.getRawParameterValue (params.at(Names::Osc1_Pitch_Env1));
            auto& osc1PitchEnv2 = *apvts.getRawParameterValue (params.at(Names::Osc1_Pitch_Env2));
            auto& osc1PitchLfo1 = *apvts.getRawParameterValue (params.at(Names::Osc1_Pitch_Lfo1));;
            auto& osc1PitchLfo2 = *apvts.getRawParameterValue (params.at(Names::Osc1_Pitch_Lfo2));;
            auto& osc1PitchVel = *apvts.getRawParameterValue (params.at(Names::Osc1_Pitch_Vel));;
            auto& osc1PitchMod = *apvts.getRawParameterValue (params.at(Names::Osc1_Pitch_Mod));;
            
            auto& osc2PitchEnv1 = *apvts.getRawParameterValue (params.at(Names::Osc2_Pitch_Env1));
            auto& osc2PitchEnv2 = *apvts.getRawParameterValue (params.at(Names::Osc2_Pitch_Env2));
            auto& osc2PitchLfo1 = *apvts.getRawParameterValue (params.at(Names::Osc2_Pitch_Lfo1));;
            auto& osc2PitchLfo2 = *apvts.getRawParameterValue (params.at(Names::Osc2_Pitch_Lfo2));;
            auto& osc2PitchVel = *apvts.getRawParameterValue (params.at(Names::Osc2_Pitch_Vel));;
            auto& osc2PitchMod = *apvts.getRawParameterValue (params.at(Names::Osc2_Pitch_Mod));;
            
            auto& osc3PitchEnv1 = *apvts.getRawParameterValue (params.at(Names::Osc3_Pitch_Env1));
            auto& osc3PitchEnv2 = *apvts.getRawParameterValue (params.at(Names::Osc3_Pitch_Env2));
            auto& osc3PitchLfo1 = *apvts.getRawParameterValue (params.at(Names::Osc3_Pitch_Lfo1));;
            auto& osc3PitchLfo2 = *apvts.getRawParameterValue (params.at(Names::Osc3_Pitch_Lfo2));;
            auto& osc3PitchVel = *apvts.getRawParameterValue (params.at(Names::Osc3_Pitch_Vel));;
            auto& osc3PitchMod = *apvts.getRawParameterValue (params.at(Names::Osc3_Pitch_Mod));;
            
            auto& cutoffEnv1 = *apvts.getRawParameterValue (params.at(Names::Cutoff_Env1));
            auto& cutoffEnv2 = *apvts.getRawParameterValue (params.at(Names::Cutoff_Env2));
            auto& cutoffLfo1 = *apvts.getRawParameterValue (params.at(Names::Cutoff_Lfo1));;
            auto& cutoffLfo2 = *apvts.getRawParameterValue (params.at(Names::Cutoff_Lfo2));;
            auto& cutoffVel = *apvts.getRawParameterValue (params.at(Names::Cutoff_Vel));;
            auto& cutoffMod = *apvts.getRawParameterValue (params.at(Names::Cutoff_Mod));;
            
            auto& pWEnv1 = *apvts.getRawParameterValue (params.at(Names::PW_Env1));
            auto& pWEnv2 = *apvts.getRawParameterValue (params.at(Names::PW_Env2));
            auto& pWLfo1 = *apvts.getRawParameterValue (params.at(Names::PW_Lfo1));;
            auto& pWLfo2 = *apvts.getRawParameterValue (params.at(Names::PW_Lfo2));;
            auto& pWVel = *apvts.getRawParameterValue (params.at(Names::PW_Vel));;
            auto& pWMod = *apvts.getRawParameterValue (params.at(Names::PW_Mod));;
            
            auto& modEnabled = *apvts.getRawParameterValue (params.at(Names::Mod_Enabled));
            
            auto& masterGain = *apvts.getRawParameterValue (params.at(Names::Master_Gain));
            auto& nrOfVoices = *apvts.getRawParameterValue (params.at(Names::Nr_Of_Voices));
            auto& pitchBend = *apvts.getRawParameterValue (params.at(Names::Pitch_Bend));;
            auto& masterEnabled = *apvts.getRawParameterValue (params.at(Names::Master_Enabled));
            
            auto& osc1 = voice->getOsc1();
            auto& osc2 = voice->getOsc2();
            auto& osc3 = voice->getOsc3();
            auto& filter = voice->getFilter();
            auto& env1 = voice->getEnv1();
            auto& env2 = voice->getEnv2();
            auto& env3 = voice->getEnv3();
            auto& lfo1 = voice->getLfo1();
            auto& lfo2 = voice->getLfo2();
            auto& modMatrix = voice->getModMatrix();
            auto& master = voice->getMaster();
            
//            osc1.setParams (osc1Wave, osc1Semitones, osc1Cents, osc1Level, osc1PulseWidth, osc1Enabled, osc1Sync, 0);
//            osc2.setParams (osc2Wave, osc2Semitones, osc2Cents, osc2Level, osc2PulseWidth, osc2Enabled, 0, osc2FM);
//            osc3.setParams (osc3Wave, osc3Semitones, osc3Cents, osc3Level, osc3PulseWidth, osc3Enabled, 0, 0);
            voice->updateOsc1(osc1Wave, osc1Semitones, osc1Cents, osc1Level, osc1PulseWidth, osc1Enabled, osc1Sync, 0);
            voice->updateOsc2(osc2Wave, osc2Semitones, osc2Cents, osc2Level, osc2PulseWidth, osc2Enabled, 0, osc2FM);
            voice->updateOsc3(osc3Wave, osc3Semitones, osc3Cents, osc3Level, osc3PulseWidth, osc3Enabled, 0, 0);
            
            env1.setParams (env1Attack, env1Decay, env1Sustain, env1Release, env1Key, env1Vel, env1Enabled);
            env2.setParams (env2Attack, env2Decay, env2Sustain, env2Release, env2Key, env2Vel, env2Enabled);
            env3.setParams (env3Attack, env3Decay, env3Sustain, env3Release, env3Key, env3Vel, env3Enabled);
            
//            filter.setParams (filterMode, filterCutoff, filterResonance, filterVel, filterEnv, filterKey, filterEnabled);
            voice->updateFilter(filterMode, filterCutoff, filterResonance, filterVel, filterKey, filterEnabled, filterEnv);
            
            modMatrix.setEnabled(modEnabled);
            modMatrix.setOsc1PitchModParams(osc1PitchEnv1, osc1PitchEnv2, osc1PitchLfo1, osc1PitchLfo2, osc1PitchVel, osc1PitchMod);
            modMatrix.setOsc2PitchModParams(osc2PitchEnv1, osc2PitchEnv2, osc2PitchLfo1, osc2PitchLfo2, osc2PitchVel, osc2PitchMod);
            modMatrix.setOsc3PitchModParams(osc3PitchEnv1, osc3PitchEnv2, osc3PitchLfo1, osc3PitchLfo2, osc3PitchVel, osc3PitchMod);
            modMatrix.setCutoffModParams(cutoffEnv1, cutoffEnv2, cutoffLfo1, cutoffLfo2, cutoffVel, cutoffMod);
            modMatrix.setPWModParams(pWEnv1,  pWEnv2,  pWLfo1,  pWLfo2,  pWVel,  pWMod);
            voice->updateMod(ModMatrix::Source::Env1, ModMatrix::Destination::Osc1Pitch, osc1PitchEnv1, filterCutoff, osc1PulseWidth, osc1PitchVel, osc1PitchMod);
            voice->updateMod(ModMatrix::Source::Env1, ModMatrix::Destination::Osc2Pitch, osc2PitchEnv1, filterCutoff, osc2PulseWidth, osc2PitchVel, osc2PitchMod);
            voice->updateMod(ModMatrix::Source::Env1, ModMatrix::Destination::Osc3Pitch, osc3PitchEnv1, filterCutoff, osc3PulseWidth, osc3PitchVel, osc3PitchMod);
            voice->updateMod(ModMatrix::Source::Env2, ModMatrix::Destination::Osc1Pitch, osc1PitchEnv2, filterCutoff, osc1PulseWidth, osc1PitchVel, osc1PitchMod);
            voice->updateMod(ModMatrix::Source::Env2, ModMatrix::Destination::Osc2Pitch, osc2PitchEnv2, filterCutoff, osc2PulseWidth, osc2PitchVel, osc2PitchMod);
            voice->updateMod(ModMatrix::Source::Env2, ModMatrix::Destination::Osc3Pitch, osc3PitchEnv2, filterCutoff, osc3PulseWidth, osc3PitchVel, osc3PitchMod);
            voice->updateMod(ModMatrix::Source::Lfo1, ModMatrix::Destination::Osc1Pitch, osc1PitchLfo1, filterCutoff, osc1PulseWidth, osc1PitchVel, osc1PitchMod);
            voice->updateMod(ModMatrix::Source::Lfo1, ModMatrix::Destination::Osc2Pitch, osc2PitchLfo1, filterCutoff, osc2PulseWidth, osc2PitchVel, osc2PitchMod);
            voice->updateMod(ModMatrix::Source::Lfo1, ModMatrix::Destination::Osc3Pitch, osc3PitchLfo1, filterCutoff, osc3PulseWidth, osc3PitchVel, osc3PitchMod);
            voice->updateMod(ModMatrix::Source::Lfo2, ModMatrix::Destination::Osc1Pitch, osc1PitchLfo2, filterCutoff, osc1PulseWidth, osc1PitchVel, osc1PitchMod);
            voice->updateMod(ModMatrix::Source::Lfo2, ModMatrix::Destination::Osc2Pitch, osc2PitchLfo2, filterCutoff, osc2PulseWidth, osc2PitchVel, osc2PitchMod);
            voice->updateMod(ModMatrix::Source::Lfo2, ModMatrix::Destination::Osc3Pitch, osc3PitchLfo2, filterCutoff, osc3PulseWidth, osc3PitchVel, osc3PitchMod);
//            voice->updateMod(ModMatrix::Source::Vel, ModMatrix::Destination::Osc1Pitch, osc1PitchVel, filterCutoff, osc1PulseWidth, osc1PitchVel, osc1PitchMod);
//            voice->updateMod(ModMatrix::Source::Vel, ModMatrix::Destination::Osc2Pitch, osc2PitchVel, filterCutoff, osc2PulseWidth, osc2PitchVel, osc2PitchMod);
//            voice->updateMod(ModMatrix::Source::Vel, ModMatrix::Destination::Osc3Pitch, osc3PitchVel, filterCutoff, osc3PulseWidth, osc3PitchVel, osc3PitchMod);
//            voice->updateMod(ModMatrix::Source::ModWheel, ModMatrix::Destination::Osc1Pitch, osc1PitchMod, filterCutoff, osc1PulseWidth, osc1PitchVel, osc1PitchMod);
//            voice->updateMod(ModMatrix::Source::ModWheel, ModMatrix::Destination::Osc2Pitch, osc2PitchMod, filterCutoff, osc2PulseWidth, osc2PitchVel, osc2PitchMod);
//            voice->updateMod(ModMatrix::Source::ModWheel, ModMatrix::Destination::Osc3Pitch, osc3PitchMod, filterCutoff, osc3PulseWidth, osc3PitchVel, osc3PitchMod);
            
            lfo1.setParams (lfo1Source, lfo1Destination, lfo1Wave, lfo1Rate, lfo1Gain, lfo1Reset, lfo1Enabled);
            lfo2.setParams (lfo2Source, lfo2Destination, lfo2Wave, lfo2Rate, lfo2Gain, lfo2Reset, lfo2Enabled);
            voice->updateLfo(lfo1, lfo1Source, lfo1Destination, lfo1Wave, lfo1Rate, lfo1Gain, lfo1Reset, lfo1Enabled, filterCutoff);
            voice->updateLfo(lfo2, lfo2Source, lfo2Destination, lfo2Wave, lfo2Rate, lfo2Gain, lfo2Reset, lfo2Enabled);
            
            master.setParams(masterGain, nrOfVoices, pitchBend, masterEnabled);
            
            
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GMSQ1AudioProcessor();
}
