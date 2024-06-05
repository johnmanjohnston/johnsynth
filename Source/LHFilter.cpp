/*
  ==============================================================================

    LHFilter.cpp
    Created: 1 Jun 2024 9:03:03pm
    Author:  USER

  ==============================================================================
*/

#include "LHFilter.h"

/*
void LHFilter::applyHighCut(juce::AudioBuffer<float> buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    lowpassIIR.process(context);
}
*/

void LHFilter::process(juce::AudioBuffer<float> buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    lpf.process(context);
}

void LHFilter::prepare(const juce::dsp::ProcessSpec& spec)
{
    lpf.prepare(spec);
    lpf.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
}

void LHFilter::updateFilters(double sampleRate, float lowFrequency, float lowResonance)
{
    lpf.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    lpf.state->setCutOffFrequency(sampleRate, lowFrequency, lowResonance);

    previousLowFreq = lowFrequency;
    previousLowRes = lowResonance;
}

bool LHFilter::parametersMatch(float lowFrequency, float lowResonance)
{
    if (lowFrequency != previousLowFreq) return false;
    if (lowResonance != previousLowRes) return false;

    return true;
}
