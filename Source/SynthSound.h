/*
  ==============================================================================

    SynthSound.h
    Created: 12 Mar 2022 7:57:54pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>



class SynthSound : public juce::SynthesiserSound
{
    
public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiNoteNumber) override
    {
        return true;
    }
};
