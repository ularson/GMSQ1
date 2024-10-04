/*
  ==============================================================================

    SynthVoice.cpp
    Created: 12 Mar 2022 7:57:25pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#include "SynthVoice.h"
#include "GUI/Utilities.h"

//=======================================================

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast <juce::SynthesiserSound*>(sound) != nullptr;
}

//=======================================================

void SynthVoice::setPitchBend(int pitchWheelPos)
{
    if (pitchWheelPos > 8192)
    {
        // shifting up
        pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
    }
    else
    {
        // shifting down
        pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
    }
}

float SynthVoice::pitchBendCents()
{
    if (pitchBend >= 0.0f)
    {
        // shifting up
        return pitchBend * pitchBendUpSemitones * 100;
    }
    else
    {
        // shifting down
        return pitchBend * pitchBendDownSemitones * 100;
    }
}

double SynthVoice::noteHz(int midiNoteNumber, double centsOffset)
{
    double hertz = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    hertz *= std::pow(2.0, centsOffset / 1200);
    return hertz;
}

//=======================================================

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    setPitchBend(newPitchWheelValue);
    frequency = noteHz(noteNumber, pitchBendCents());
}

//=======================================================

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    if(controllerNumber == 1)
        modWheel = newControllerValue;
}

//=======================================================

void SynthVoice::startNote (int midiNoteNumber, float vel, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    juce::ignoreUnused(midiNoteNumber);
    
    noteNumber = midiNoteNumber;
    frequency = noteHz(midiNoteNumber, 0);
    velocity = vel;
    setPitchBend(currentPitchWheelPosition);
    
    osc1.setFreq(noteNumber);
    osc1.setLevel(velocity);
    osc2.setFreq(noteNumber);
    osc2.setLevel(velocity);
    osc3.setFreq(noteNumber);
    osc3.setLevel(velocity);
    env1.noteOn();
    env2.noteOn();
    env3.noteOn();
}

//=======================================================

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    env1.noteOff();
    env2.noteOff();
    env3.noteOff();
    
    if(!allowTailOff || !env3.isActive())
        clearCurrentNote();
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    if(osc1.enabled) {
        osc1.prepare(spec);
        osc1.setWave(Const::SINE_WAVE, Const::PULSE_WIDTH);
    }
    if(osc2.enabled) {
        osc2.prepare(spec);
        osc2.setWave(Const::SINE_WAVE, Const::PULSE_WIDTH);
    }
    if(osc1.enabled) {
        osc3.prepare(spec);
        osc3.setWave(Const::SINE_WAVE, Const::PULSE_WIDTH);
    }
    
    if(filter.enabled) {
        filter.prepare(spec);
        filter.setCutoffFrequencyHz(Const::MAX_FREQUENCY);
    }
    
    if(env1.enabled) {
        env1.setSampleRate(sampleRate);
    }
    
    if(env2.enabled) {
        env2.setSampleRate(sampleRate);
    }
    
    if(env3.enabled) {
        env3.setSampleRate(sampleRate);
    }
    
    if(lfo1.enabled) {
        lfo1.prepare(spec);
        lfo1.setWave(Const::SINE_WAVE);
    }
    
    if(lfo2.enabled) {
        lfo2.prepare(spec);
        lfo2.setWave(Const::SINE_WAVE);
    }
    
    master.prepare(spec);
    master.setNrOfvoices(Const::NR_OF_VOICES);
    master.setPitchBend(Const::PITCH_BEND);
    master.setGainLinear(0.1f);
}

//=======================================================

void SynthVoice::renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
    if(!isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    env1.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    env2.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> block(synthBuffer);
    osc1.process(juce::dsp::ProcessContextReplacing<float> (block));
    osc2.process(juce::dsp::ProcessContextReplacing<float> (block));
    osc3.process(juce::dsp::ProcessContextReplacing<float> (block));

    filter.process(juce::dsp::ProcessContextReplacing<float> (block));
    env3.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    master.process(juce::dsp::ProcessContextReplacing<float> (block));
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if(!env3.isActive())
            clearCurrentNote();
        
    }
}

void SynthVoice::updateOsc1(const int wave, const float semitones, const float cents, const float level, const float PW, const bool enabled, const float sync, const float FM)
{
    osc1.setParams(wave, semitones, cents, level, PW, enabled, sync, FM);
}

void SynthVoice::updateOsc2(const int wave, const float semitones, const float cents, const float level, const float PW, const bool enabled, const float sync, const float FM)
{
    osc2.setParams(wave, semitones, cents, level, PW, enabled, sync, FM);
}

void SynthVoice::updateOsc3(const int wave, const float semitones, const float cents, const float level, const float PW, const bool enabled, const float sync, const float FM)
{
    osc3.setParams(wave, semitones, cents, level, PW, enabled, sync, FM);
}

void SynthVoice::updateFilter(const int mode, const float cutoff, const float resonance, const float vel, const float key, const bool enabled, const float env)
{
    auto env1Adsr = env1.getNextSample();
    auto filterCutoff = key > 0 ? cutoff * key / (log2(128.f / (noteNumber + 1))) : cutoff;
    auto filterVel = vel > 0 ? cutoff * velocity * vel : cutoff;

    filter.setParams(mode, filterCutoff, resonance, filterVel, key, enabled, env1Adsr * env);
}

void SynthVoice::updateLfo(LFO& lfo, const int source, const int destination, const int wave, const float rate, const float gain, const bool reset, const bool enabled, const float cutoff)
{
    if(enabled) {
        auto lfoRate = lfo.getFrequency() * rate * gain;
        auto lfoCutoff = juce::jlimit(20.f, 20000.f, cutoff * lfoRate);
        auto lfoPW = juce::jlimit(0.f, 2.f, lfoRate);
        
        switch (destination) {
            case LFO::Destinations::Pitch:
                osc1.setFrequency(osc1.getFrequency() + lfoRate);
                osc2.setFrequency(osc2.getFrequency() + lfoRate);
                osc3.setFrequency(osc3.getFrequency() + lfoRate);
                break;
            case LFO::Destinations::Cutoff:
                filter.setCutoffFrequencyHz(lfoCutoff);
                break;
            case LFO::Destinations::PW:
                osc1.setPulseWidth(osc1.getPulseWidth() * lfoPW);
                osc2.setPulseWidth(osc2.getPulseWidth() * lfoPW);
                osc3.setPulseWidth(osc3.getPulseWidth() * lfoPW);
                break;
            default:
                break;
        }
    }
}

void SynthVoice::updateMod(const int source, const int destination, const int mod, const float cutoff, const float pulseWidth, const float vel, const float modWheel)
{
    auto env1Mod = mod > 0 ? env1.getNextSample() * mod : 1.0;
    auto env2Mod = mod > 0 ? env2.getNextSample() * mod : 1.0;
    auto lfo1Mod = lfo1.getFrequency() * mod;
    auto lfo2Mod = lfo2.getFrequency() * mod;
    
    if(modMatrix.getEnabled() == false)
    {
        return;
    }

    switch (source) {
        case ModMatrix::Source::Env1:
            switch (destination) {
                case ModMatrix::Destination::Osc1Pitch:
                    osc1.setFrequency(osc1.getFrequency() * env1Mod);
                    break;
                case ModMatrix::Destination::Osc2Pitch:
                    osc2.setFrequency(osc2.getFrequency() * env1Mod);
                    break;
                case ModMatrix::Destination::Osc3Pitch:
                    osc3.setFrequency(osc3.getFrequency() * env1Mod);
                    break;
                case ModMatrix::Destination::FilterCutoff:
                    filter.setCutoffFrequencyHz(cutoff * env1Mod);
                    break;
                case ModMatrix::Destination::PulseWidth:
                    osc1.setWave(Const::PULSE_WAVE, pulseWidth * env1Mod);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case ModMatrix::Source::Env2:
            switch (destination) {
                case ModMatrix::Destination::Osc1Pitch:
                    osc1.setFrequency(osc1.getFrequency() * env2Mod);
                    break;
                case ModMatrix::Destination::Osc2Pitch:
                    osc2.setFrequency(osc2.getFrequency() * env2Mod);
                    break;
                case ModMatrix::Destination::Osc3Pitch:
                    osc3.setFrequency(osc3.getFrequency() * env2Mod);
                    break;
                case ModMatrix::Destination::FilterCutoff:
                    filter.setCutoffFrequencyHz(cutoff * env2Mod);
                    break;
                case ModMatrix::Destination::PulseWidth:
                    osc1.setWave(Const::PULSE_WAVE, pulseWidth * env2Mod);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case ModMatrix::Source::Lfo1:
            switch (destination) {
                case ModMatrix::Destination::Osc1Pitch:
                    osc1.setFrequency(osc1.getFrequency() + lfo1Mod);
                    break;
                case ModMatrix::Destination::Osc2Pitch:
                    osc2.setFrequency(osc2.getFrequency() + lfo1Mod);
                    break;
                case ModMatrix::Destination::Osc3Pitch:
                    osc3.setFrequency(osc3.getFrequency() + lfo1Mod);
                    break;
                case ModMatrix::Destination::FilterCutoff:
                    filter.setCutoffFrequencyHz(cutoff + lfo1Mod);
                    break;
                case ModMatrix::Destination::PulseWidth:
                    osc1.setWave(Const::PULSE_WAVE, pulseWidth + lfo1Mod);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case ModMatrix::Source::Lfo2:
            switch (destination) {
                case ModMatrix::Destination::Osc1Pitch:
                    osc1.setFrequency(osc1.getFrequency() + lfo2Mod);
                    break;
                case ModMatrix::Destination::Osc2Pitch:
                    osc2.setFrequency(osc2.getFrequency() + lfo2Mod);
                    break;
                case ModMatrix::Destination::Osc3Pitch:
                    osc3.setFrequency(osc3.getFrequency() + lfo2Mod);
                    break;
                case ModMatrix::Destination::FilterCutoff:
                    filter.setCutoffFrequencyHz(cutoff + lfo2Mod);
                    break;
                case ModMatrix::Destination::PulseWidth:
                    osc1.setWave(Const::PULSE_WAVE, pulseWidth + lfo2Mod);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case ModMatrix::Source::Vel:
            switch (destination) {
                case ModMatrix::Destination::Osc1Pitch:
                    osc1.setFrequency(osc1.getFrequency() * vel);
                    break;
                case ModMatrix::Destination::Osc2Pitch:
                    osc2.setFrequency(osc2.getFrequency() * vel);
                    break;
                case ModMatrix::Destination::Osc3Pitch:
                    osc3.setFrequency(osc3.getFrequency() * vel);
                    break;
                case ModMatrix::Destination::FilterCutoff:
                    filter.setCutoffFrequencyHz(cutoff * vel);
                    break;
                case ModMatrix::Destination::PulseWidth:
                    osc1.setWave(Const::PULSE_WAVE, pulseWidth * vel);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case ModMatrix::Source::ModWheel:
            switch (destination) {
                case ModMatrix::Destination::Osc1Pitch:
                    osc1.setFrequency(osc1.getFrequency() * modWheel);
                    break;
                case ModMatrix::Destination::Osc2Pitch:
                    osc2.setFrequency(osc2.getFrequency() * modWheel);
                    break;
                case ModMatrix::Destination::Osc3Pitch:
                    osc3.setFrequency(osc3.getFrequency() * modWheel);
                    break;
                case ModMatrix::Destination::FilterCutoff:
                    filter.setCutoffFrequencyHz(cutoff * modWheel);
                    break;
                case ModMatrix::Destination::PulseWidth:
                    osc1.setWave(Const::PULSE_WAVE, pulseWidth * modWheel);
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

