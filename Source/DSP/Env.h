/*
  ==============================================================================

    AdsrData.h
    Created: 7 Feb 2021 2:29:21pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct Env : public juce::ADSR
{
public:
    void setParams (const float attack, const float decay, const float sustain, const float release, const float key, const float vel, const bool enabled);
    bool enabled { true };
private:
    juce::ADSR::Parameters adsrParams;
    void disableEnv ();
};
