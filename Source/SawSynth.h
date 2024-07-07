/*
  ==============================================================================

    SawSynth.h
    Created: 6 Jul 2024 10:42:47am
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#define SAW_OSC juce::dsp::Oscillator<float>{ [](float x) { return (x / juce::MathConstants<float>::pi); } }
#define BASS_SAW_OSC juce::dsp::Oscillator<float>{ [](float x) { return 0.5f * (x / juce::MathConstants<float>::pi); } }

class JOscillator {
public:
    bool isPrepared = false;
    juce::dsp::Oscillator<float> osc{ [](float x) { return x / juce::MathConstants<float>::pi; } };

    float detuneAmounts[8] = { -.01f, -0.009f, -0.006f, -0.003f, 0.01f, 0.006f, 0.009f, 0.02f };

    juce::dsp::Oscillator<float> unisons[8] = 
    {
        SAW_OSC, SAW_OSC,
        SAW_OSC, SAW_OSC,
        SAW_OSC, SAW_OSC,
        SAW_OSC, SAW_OSC,
    };

    juce::dsp::Oscillator<float> bassUnisons[8] =
    {
        BASS_SAW_OSC, BASS_SAW_OSC,
        BASS_SAW_OSC, BASS_SAW_OSC,
        BASS_SAW_OSC, BASS_SAW_OSC,
        BASS_SAW_OSC, BASS_SAW_OSC,
    };

    juce::dsp::Oscillator<float> bassOsc{ [](float x) { return x / juce::MathConstants<float>::pi; } };

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

    juce::AudioBuffer<float> tempAudioBuffer;
    juce::dsp::AudioBlock<float> tempBlock;
    juce::HeapBlock<char> heapBlock;
};