/*
  ==============================================================================

    Master.cpp
    Created: 16 Apr 2024 12:31:03am
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "Master.h"



void Master::setGain(const float level)
{
    setGainLinear(level);
}

void Master::setNrOfVoices(const float voices)
{
    nrOfvoices = voices;
}

void Master::setPitchBend(const float bendRange)
{
    pitchBend = bendRange;
}

void Master::setParams (const float level, const int voices, const int pitchBend, const bool enabled)
{
    if(enabled)
    {
        setGain(level);
        setNrOfVoices(voices);
        setPitchBend(pitchBend);
    } else {
        disableMaster();
    }
}

void Master::disableMaster()
{
    setGain(Const::MASTER_GAIN);
    setNrOfVoices(Const::NR_OF_VOICES);
    setPitchBend(Const::PITCH_BEND);
}

void Master::setNrOfvoices(int voices) {
    nrOfvoices = voices;
}

int Master::getNrOfvoices() {
    return nrOfvoices;
}

void Master::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    prepare (spec);
}

void Master::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block { buffer };
    process (juce::dsp::ProcessContextReplacing<float>(block));
}
