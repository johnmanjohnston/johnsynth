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
    lowpassIIR.process(context);
}

void LHFilter::prepare(const juce::dsp::ProcessSpec& spec)
{
    lowpassIIR.state = juce::dsp::IIR::Coefficients<float>::makeLowPass(spec.sampleRate, 2000.f);
    lowpassIIR.prepare(spec);
}
