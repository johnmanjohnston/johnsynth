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
    void applyLowCut(juce::AudioBuffer<float> buffer);
    void applyHighCut(juce::AudioBuffer<float> buffer);

    void prepare(const juce::dsp::ProcessSpec& spec);

    // dsp
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowpassIIR;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highpassIIR;
};