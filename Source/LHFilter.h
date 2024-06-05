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

    float previousHighFreq;
    float previousHighRes;

    // dsp
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter <float>, juce::dsp::StateVariableFilter::Parameters <float>> lpf;
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter <float>, juce::dsp::StateVariableFilter::Parameters <float>> hpf;
    
    void updateFilters(double sampleRate, float lowFrequency, float lowResonance, float highFrequency, float highResonance);
    bool parametersMatch(float lowFrequency, float lowResonance, float highFrequency, float highResonance);
};