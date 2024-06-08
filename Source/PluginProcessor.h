/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SawSampler.h"
#include "Width.h"
#include "LHFilter.h"
#include "LFO.h"

//==============================================================================
/**
*/
class JohnSynthAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    JohnSynthAudioProcessor();
    ~JohnSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::MidiKeyboardState kbState;

    SawSampler sawSampler;
    SawSampler harmSawSampler;

    LFO lfo;

    Widener widener;
    LHFilter filter;
    juce::dsp::Limiter<float> masterLimiter;
    juce::dsp::Compressor<float> masterCompressor;
    juce::dsp::Compressor<float> harmonyCompressor;

    juce::dsp::Gain<float> harmonyGain;
    juce::dsp::Gain<float> mainGain;
    juce::dsp::Gain<float> masterGain;

    juce::AudioParameterFloat* lpFreq;
    juce::AudioParameterFloat* lpRes;

    juce::AudioParameterFloat* hpFreq;
    juce::AudioParameterFloat* hpRes;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JohnSynthAudioProcessor)
};
