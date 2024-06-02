/*
  ==============================================================================

    LHFilter.cpp
    Created: 1 Jun 2024 9:03:03pm
    Author:  USER

  ==============================================================================
*/

#include "LHFilter.h"

// TODO: you should probably put application of low cut and high cut into one function
void LHFilter::applyLowCut(juce::AudioBuffer<float> buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    highpassIIR.process(context);
}

void LHFilter::applyHighCut(juce::AudioBuffer<float> buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    lowpassIIR.process(context);
}

void LHFilter::prepare(const juce::dsp::ProcessSpec& spec)
{
    lowpassIIR.state = juce::dsp::IIR::Coefficients<float>::makeLowPass(spec.sampleRate, 18000.f);
    lowpassIIR.prepare(spec);

    highpassIIR.state = juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate, 1000.f);
    highpassIIR.prepare(spec);
}
