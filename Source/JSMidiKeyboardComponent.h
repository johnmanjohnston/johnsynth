/*
  ==============================================================================

    JSMidiKeyboardComponent.h
    Created: 1 Jun 2024 2:08:53pm
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

using namespace juce;

class JSMidiKeyboardComponent : public juce::MidiKeyboardComponent
{
public:
    JSMidiKeyboardComponent(MidiKeyboardState& state, Orientation orientation);

protected:
    virtual void 	drawWhiteNote(int midiNoteNumber, Graphics& g, Rectangle< float > area, bool isDown, bool isOver, Colour lineColour, Colour textColour) override;
    virtual void 	drawBlackNote(int midiNoteNumber, Graphics& g, Rectangle< float > area, bool isDown, bool isOver, Colour noteFillColour) override;

    static const juce::Font getHelveticaLight()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::HelveticaLight_ttf, BinaryData::HelveticaLight_ttfSize);
        return typeface;
    }
};