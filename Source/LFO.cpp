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
    osc.prepare(spec);
    
    // TODO: allow user to change oscillator waveform. for now, we'll just hardcode it to be a sine wave
    osc.initialise([](float x) { return std::sin(x); });
}

void LFO::setFrequency(float frequency)
{
    osc.setFrequency(frequency);
}

float LFO::getFrequency()
{
    return osc.getFrequency();
}

float LFO::step()
{
    // TODO
}
