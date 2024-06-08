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
    float frequency;
    float normalizedFrequency;
    float sampleRate;
    float lfoValue;

    juce::dsp::Phase<float> phase;

    void prepare(juce::dsp::ProcessSpec spec);
    void setFrequency(float frequency);
    float getFrequency();
    float getLFOvalue();
    void tick();
    void reset();

    std::function<float(float)> lfoCalculation = [](float x){ return std::sin(x) * 5.f; };
};