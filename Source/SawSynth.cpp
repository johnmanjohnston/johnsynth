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
    osc.changeRampTime(.05f);

    adsrParams.attack = 0.005f;
    adsrParams.decay = 1.f;
    adsrParams.sustain = 1.f;
    adsrParams.release = 0.002f;

    adsr.setSampleRate(spec.sampleRate);
    adsr.setParameters(adsrParams);

    this->isPrepared = true;
}

// voice
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.adsr.noteOn();
    osc.osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    osc.adsr.noteOff();
    clearCurrentNote();
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    juce::AudioBuffer<float> synthesisBufferProxy(outputBuffer.getArrayOfWritePointers(), 2, startSample, numSamples);
    juce::dsp::AudioBlock<float> audioBlock{ synthesisBufferProxy };

    osc.osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    osc.adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}

void SynthVoice::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    osc.prepare(spec);
}
