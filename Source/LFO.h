/*
  ==============================================================================

    LFO.h
    Created: 8 Jun 2024 7:46:48pm
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LFO 
{
public:
    juce::dsp::Oscillator<float> osc;

    void prepare(juce::dsp::ProcessSpec spec);
    void setFrequency(float frequency);
    float getFrequency();
    float step();
};