/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JohnSynthAudioProcessorEditor::JohnSynthAudioProcessorEditor (JohnSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), kbComponent(p.kbState, juce::KeyboardComponentBase::horizontalKeyboard),
    lpAttachment(*p.lpFreq, lpSlider), lpresAttachment(*p.lpRes, lpresSlider), hpAttachment(*p.hpFreq, hpSlider), hpresAttachment(*p.hpRes, hpresSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (850, 500);
    addAndMakeVisible(kbComponent);

    addAndMakeVisible(lpSlider);
    addAndMakeVisible(lpresSlider);

    addAndMakeVisible(hpSlider);
    addAndMakeVisible(hpresSlider);

}

JohnSynthAudioProcessorEditor::~JohnSynthAudioProcessorEditor()
{
    lpSlider.setLookAndFeel(nullptr);
    lpresSlider.setLookAndFeel(nullptr);
    hpSlider.setLookAndFeel(nullptr);
    hpresSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void JohnSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(10, 10, 10));
    g.setFont(getHelveticaLight());

    g.setFont(34.f);
    g.setColour (juce::Colour(100, 100, 100));
    g.drawText("johnsynth", 14, 0, 150, 50, juce::Justification::left, false);

    g.setFont(14.f);
    g.drawFittedText("JohnSynth is free and open-source, programmed by Ethan John (johnmanjohnston)\nand is available at https://github.com/johnmanjohnston/johnsynth/", 14, 380, 700, 100, juce::Justification::left, false);
    
    filterPanel->paint(g);
    adsrPanel->paint(g);
    ottPanel->paint(g);

    lpSlider.setLookAndFeel(&jsLookAndFeel);
    lpresSlider.setLookAndFeel(&jsLookAndFeel);
    hpSlider.setLookAndFeel(&jsLookAndFeel);
    hpresSlider.setLookAndFeel(&jsLookAndFeel);
   // lpSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 200);
    lpSlider.setTextValueSuffix("hz - HIGH CUT");
    lpresSlider.setTextValueSuffix(" - HIGH CUT RESONANCE");
    hpSlider.setTextValueSuffix("hz - LOW CUT");
    hpresSlider.setTextValueSuffix(" - LOW CUT RESONANCE");
}

void JohnSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    kbComponent.setBounds(0, 420, 850, 80);

    //lpSlider.setBounds(70, 120, 200, 60);
    lpSlider.setBounds(filterPanel->x + 14, filterPanel->y + 30,    filterPanel->width - 28, 60);
    lpresSlider.setBounds(filterPanel->x + 14, filterPanel->y + 60, filterPanel->width - 28, 60);

    hpSlider.setBounds(filterPanel->x + 14, filterPanel->y + 90, filterPanel->width - 28, 60);
    hpresSlider.setBounds(filterPanel->x + 14, filterPanel->y + 120, filterPanel->width - 28, 60);
}
