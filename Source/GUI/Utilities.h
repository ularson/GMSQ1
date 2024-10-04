/*
  ==============================================================================

    Utilities.h
    Created: 13 Apr 2024 11:14:02pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"

namespace Const
{
static constexpr float MIN_FREQUENCY = 20.f;
static constexpr float MAX_FREQUENCY = 20000.f;
static constexpr int SINE_WAVE = 0;
static constexpr int SAW_WAVE = 1;
static constexpr int SQUARE_WAVE = 2;
static constexpr int TRIANGLE_WAVE = 3;
static constexpr int PULSE_WAVE = 4;
static constexpr int NOISE_WAVE = 5;
static constexpr int LPF24 = 0;
static constexpr int LPF12 = 1;
static constexpr int BPF24 = 2;
static constexpr int BPF12 = 3;
static constexpr int HPF24 = 4;
static constexpr int HPF12 = 5;
static constexpr float MASTER_GAIN = 0.5f;
static constexpr int NR_OF_VOICES = 16;
static constexpr int PITCH_BEND = 2;
static constexpr int PULSE_WIDTH = 0;
}

namespace GMSQ1
{
    template<
        typename APVTS,
        typename Params,
        typename Name
            >
    juce::RangedAudioParameter& getParam(APVTS& apvts, const Params& params, const Name& name)
    {
        auto param = apvts.getParameter(params.at(name));
        jassert( param != nullptr );
        
        return *param;
    }

    template<
        typename Attachment,
        typename APVTS,
        typename Params,
        typename ParamName,
        typename SliderType
            >
    void makeAttachment(std::unique_ptr<Attachment>& attachment,
                        APVTS& apvts,
                        const Params& params,
                        const ParamName& name,
                        SliderType& slider)
    {
        attachment = std::make_unique<Attachment>(apvts,
                                                  params.at(name),
                                                  slider);
    }

    juce::String getValString(const juce::RangedAudioParameter& param,
                              bool getLow,
                              juce::String suffix);

    template<typename T>
    bool truncateKiloValue(T& value)
    {
        if( value > static_cast<T>(999))
        {
            value /= static_cast<T>(1000);
            return true;
        }
        
        return false;
    }

    juce::Rectangle<int> getModuleBackgroundArea(juce::Rectangle<int> bounds);

    void drawModuleBackground(juce::Graphics &g, juce::Rectangle<int> bounds);
}

