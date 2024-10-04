/*
  ==============================================================================

    AdsrData.cpp
    Created: 7 Feb 2021 2:29:21pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "Env.h"

void Env::setParams (const float attack, const float decay, const float sustain, const float release, const float key, const float vel, const bool enabled)
{
    
    if(enabled){
        adsrParams.attack = attack;
        adsrParams.decay = decay;
        adsrParams.sustain = sustain;
        adsrParams.release = release;
    } else {
        disableEnv();
    }
    setParameters (adsrParams);
}

void Env::disableEnv ()
{
    adsrParams.attack = 0;
    adsrParams.decay = 0;
    adsrParams.sustain = 1;
    adsrParams.release = 0;
}
