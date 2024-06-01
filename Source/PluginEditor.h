/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "JSLookAndFeel.h"
#include "JSMidiKeyboardComponent.h"

//==============================================================================
/**
*/
class JohnSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JohnSynthAudioProcessorEditor (JohnSynthAudioProcessor&);
    ~JohnSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    JSMidiKeyboardComponent kbComponent;

    static const juce::Font getHelvetica()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::Helvetica_ttf, BinaryData::Helvetica_ttfSize);
        return typeface;
    }

    static const juce::Font getHelveticaLight()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::HelveticaLight_ttf, BinaryData::HelveticaLight_ttfSize);
        return typeface;
    }
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JohnSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JohnSynthAudioProcessorEditor)
};
