/*
  ==============================================================================

    SawSynth.cpp
    Created: 6 Jul 2024 10:42:47am
    Author:  USER

  ==============================================================================
*/

#include "SawSynth.h"

// oscillator
void JOscillator::prepare(const juce::dsp::ProcessSpec& spec)
{
    osc.prepare(spec);
    osc.changeRampTime(.0f);

    bassOsc.prepare(spec);
    bassOsc.changeRampTime(0.f);

    adsrParams.attack = 0.f;
    adsrParams.decay = 1.f;
    adsrParams.sustain = 1.f;
    adsrParams.release = 0.02f;

    adsr.setSampleRate(spec.sampleRate);
    adsr.setParameters(adsrParams);

    for (int i = 0; i < 8; ++i) 
    {
        unisons[i].prepare(spec);
        unisons[i].changeRampTime(.0f);

        bassUnisons[i].prepare(spec);
        bassUnisons[i].changeRampTime(.0f);
    }

    this->isPrepared = true;
}

// voice
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    for (int i = 0; i < 8; ++i)
    {
        osc.unisons[i].setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) * (1 + osc.detuneAmounts[i]));
        osc.bassUnisons[i].setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber - 12) * (1 + osc.detuneAmounts[i]));
    }

    osc.osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    osc.bassOsc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber - 12));
    osc.adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    clearCurrentNote();
    osc.adsr.noteOff();
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (!osc.adsr.isActive()) return;

    // create audio block for temporary audio buffer
    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(tempAudioBuffer).getSubBlock(startSample, numSamples);
    audioBlock.clear();

    // create context and process oscillator, then add ADSR to the temporary audio buffer
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    osc.osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    osc.bassOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    for (int i = 0; i < 8; ++i)
    {
        osc.unisons[i].process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
        osc.bassUnisons[i].process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    }

    osc.adsr.applyEnvelopeToBuffer(tempAudioBuffer, startSample, numSamples);

    // add the temporary audio buffer to the final output buffer
    juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock((size_t)startSample, (size_t)numSamples).add(audioBlock);
}

void SynthVoice::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    osc.prepare(spec);
 
    tempBlock = juce::dsp::AudioBlock<float>(heapBlock, spec.numChannels, spec.maximumBlockSize);
    tempAudioBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
}
