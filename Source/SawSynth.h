/*
  ==============================================================================

    SawSynth.h
    Created: 6 Jul 2024 10:42:47am
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class JOscillator {
public:
    bool isPrepared = false;
    juce::dsp::Oscillator<float> osc{ [](float x) { return std::sin(x); } };

    juce::ADSR::Parameters adsrParams;
    juce::ADSR adsr;

    void prepare(const juce::dsp::ProcessSpec& spec);
};

struct SynthSound : public juce::SynthesiserSound
{
    SynthSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

class SynthVoice : public juce::SynthesiserVoice {
public:
    virtual bool    canPlaySound(juce::SynthesiserSound* sound) override { return nullptr != dynamic_cast<juce::SynthesiserSound*>(sound);; }

            void    prepareToPlay(juce::dsp::ProcessSpec& spec);
    virtual void 	startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    virtual void 	stopNote(float velocity, bool allowTailOff) override;
    virtual void 	pitchWheelMoved(int newPitchWheelValue) override;
    virtual void 	controllerMoved(int controllerNumber, int newControllerValue) override;
    virtual void 	renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

            JOscillator osc;
};