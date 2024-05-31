/*
  ==============================================================================

    JSLookAndFeel.h
    Created: 1 Jun 2024 12:17:45am
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class JSLookAndFeel : public juce::LookAndFeel_V4 
{
private:
    juce::Font getHelvetica() 
    {
        juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::Helvetica_ttf, BinaryData::HelveticaLight_ttfSize);
        juce::ScopedPointer<juce::Font> font = new juce::Font(typeface);
        font->setHeight(18);
        return *font;
    }

public:
    juce::Font getLabelFont(juce::Label& label) override 
    {
        return this->getHelvetica();
    }
};