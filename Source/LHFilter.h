/*
  ==============================================================================

    LHFilter.h
    Created: 1 Jun 2024 9:03:03pm
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LHFilter 
{
public:
    void process(juce::AudioBuffer<float> buffer);
    void prepare(const juce::dsp::ProcessSpec& spec);
    
    float previousLowFreq;
    float previousLowRes;

    // dsp
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter <float>, juce::dsp::StateVariableFilter::Parameters <float>> lpf;
    
    void updateFilters(double sampleRate, float lowFrequency, float lowResonance);
    bool parametersMatch(float lowFrequency, float lowResonance);
};