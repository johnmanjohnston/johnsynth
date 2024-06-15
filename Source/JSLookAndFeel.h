/*
  ==============================================================================

    JSLookAndFeel.h
    Created: 1 Jun 2024 12:17:45am
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;

class JSLookAndFeel : public LookAndFeel_V4 
{
private:
    Font getHelvetica() 
    {
        juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::Helvetica_ttf, BinaryData::HelveticaLight_ttfSize);
        juce::ScopedPointer<juce::Font> font = new juce::Font(typeface);
        font->setHeight(18);
        return *font;
    }

    Font getSpaceMonoBold() 
    {
        Typeface::Ptr typeface = Typeface::createSystemTypefaceFor(BinaryData::SpaceMonoBold_ttf, BinaryData::SpaceMonoBold_ttfSize);
        ScopedPointer<Font> font = new Font(typeface);
        font->setHeight(18.f);
        return *font;
    }

    Font getSpaceMono()
    {
        Typeface::Ptr typeface = Typeface::createSystemTypefaceFor(BinaryData::SpaceMonoRegular_ttf, BinaryData::SpaceMonoRegular_ttfSize);
        ScopedPointer<Font> font = new Font(typeface);
        font->setHeight(19.f);
        return *font;
    }

    /*
    juce::Font getLabelFont(juce::Label& label) override 
    {
        return this->getHelvetica();
    }

    */
public:
    JSLookAndFeel() 
    {
        setColour(juce::Slider::thumbColourId, juce::Colour(220, 220, 220));

        setColour(juce::Slider::trackColourId, juce::Colour(165, 165, 165));
        setColour(juce::Slider::backgroundColourId, juce::Colour(155, 155, 155));
        setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        //setColour(Slider::textBoxTextColourId, Colours::red);
    }

    juce::Font getLabelFont(juce::Label& label)
    {
        return getSpaceMono();
    }

    juce::Slider::SliderLayout getSliderLayout(Slider& slider)
    {
        juce::Slider::SliderLayout layout;

        layout.textBoxBounds = Rectangle<int>(0, 0, slider.getWidth(), 20);
        layout.sliderBounds = Rectangle<int>(10, 18, slider.getWidth() - 20, slider.getHeight() - 50);
        
        return layout;
    }
};