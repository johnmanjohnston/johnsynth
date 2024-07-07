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

    adsrParams.attack = 0.05f;
    adsrParams.decay = 1.f;
    adsrParams.sustain = 1.f;
    adsrParams.release = 0.02f;

    adsr.setSampleRate(spec.sampleRate);
    adsr.setParameters(adsrParams);

    this->isPrepared = true;
}

// voice
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
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
