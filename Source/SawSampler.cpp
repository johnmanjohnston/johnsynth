/*
  ==============================================================================

    SawSampler.cpp
    Created: 31 May 2024 11:10:51pm
    Author:  USER

  ==============================================================================
*/

#include "SawSampler.h"

void SawSampler::setup()
{
    for (int i = 0; i < 16; ++i) 
    {
        addVoice(new juce::SamplerVoice());
    }

    afm.registerBasicFormats();
    juce::File* file = new juce::File("C:\\Users\\USER\\Downloads\\saw.wav");
    juce::ScopedPointer<juce::AudioFormatReader> reader = afm.createReaderFor(*file);

    juce::BigInteger allNotes;
    allNotes.setRange(0, 128, true);
    addSound(new juce::SamplerSound("default", *reader, allNotes, 60, 0, 0.05, 16));
}
