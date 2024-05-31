/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JohnSynthAudioProcessorEditor::JohnSynthAudioProcessorEditor (JohnSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (850, 500);
}

JohnSynthAudioProcessorEditor::~JohnSynthAudioProcessorEditor()
{
}

//==============================================================================
void JohnSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(10, 10, 10));
    g.setFont(getHelveticaLight());

    g.setFont(30.f);
    g.setColour (juce::Colour(100, 100, 100));
    g.drawFittedText ("johnsynth", getLocalBounds(), juce::Justification::centred, 1);
}

void JohnSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
