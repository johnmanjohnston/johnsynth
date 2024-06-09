/*
  ==============================================================================

    LFO.cpp
    Created: 8 Jun 2024 7:46:48pm
    Author:  USER

  ==============================================================================
*/

#include "LFO.h"

void LFO::prepare(juce::dsp::ProcessSpec spec)
{
    sampleRate = spec.sampleRate;
    lfoCalculation = triangle;
}

void LFO::setFrequency(float frequency)
{
    this->frequency = frequency;
}

float LFO::getFrequency()
{
    return frequency;
}

float LFO::getLFOvalue()
{
    return lfoValue;
}

void LFO::tick()
{
    auto increment = juce::MathConstants<float>::twoPi * (frequency / sampleRate);
    lfoValue = lfoCalculation(phase.advance(increment) - juce::MathConstants<float>::pi);
}

void LFO::reset()
{
    phase.reset();
}
