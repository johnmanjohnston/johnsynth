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
#include "UIPanel.h"

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

    float panelSizeDivider = 1.3f;
    int horizontalSpaceBetweenPanels = 24;
    int panelLeftMargin = 96;
    int panelTopMargin = 80;

    Panel* filterPanel = new Panel(panelLeftMargin,                                                                         panelTopMargin, 265 / panelSizeDivider, 150 / panelSizeDivider, "FILTER");
    Panel* adsrPanel = new Panel(  panelLeftMargin + (265 / panelSizeDivider) + (horizontalSpaceBetweenPanels),             panelTopMargin, 265 / panelSizeDivider, 150 / panelSizeDivider, "ADSR");
    Panel* ottPanel = new Panel(   panelLeftMargin + ((265 / panelSizeDivider) * 2) + (horizontalSpaceBetweenPanels * 2),   panelTopMargin, 265 / panelSizeDivider, 150 / panelSizeDivider, "OTT");

    juce::Slider lpSlider;
    juce::SliderParameterAttachment lpAttachment;

    juce::Slider lpresSlider;
    juce::SliderParameterAttachment lpresAttachment;

    juce::Slider hpSlider;
    juce::SliderParameterAttachment hpAttachment;

    juce::Slider hpresSlider;
    juce::SliderParameterAttachment hpresAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JohnSynthAudioProcessorEditor)
};
