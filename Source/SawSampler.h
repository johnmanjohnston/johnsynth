/*
  ==============================================================================

    SawSampler.h
    Created: 31 May 2024 11:10:51pm
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SawSampler : public juce::Synthesiser 
{
public:
    void setup();

private:
    juce::AudioFormatManager afm;
};