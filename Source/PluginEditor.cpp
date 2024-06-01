/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JohnSynthAudioProcessorEditor::JohnSynthAudioProcessorEditor (JohnSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), kbComponent(p.kbState, juce::KeyboardComponentBase::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (850, 500);
    addAndMakeVisible(kbComponent);
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

    g.setFont(28.f);
    g.setColour (juce::Colour(100, 100, 100));
    //g.drawFittedText ("johnsynth", getLocalBounds(), juce::Justification::centred, 1);
    g.drawText("johnsynth", 14, 0, 150, 50, juce::Justification::left, false);
}

void JohnSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    kbComponent.setBounds(0, 400, 850, 80);
}
