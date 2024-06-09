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
        font->setHeight(22.f);
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
        return getSpaceMonoBold();
    }

    juce::Slider::SliderLayout getSliderLayout(Slider& slider)
    {
        juce::Slider::SliderLayout layout;
        layout.sliderBounds = Rectangle<int>(8, 20, 284, 18);
        layout.textBoxBounds = Rectangle<int>(0, 0, 200, 20);
        return layout;

        /*

        // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints

        int minXSpace = 0;
        int minYSpace = 0;

        auto textBoxPos = slider.getTextBoxPosition();

        if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
            minXSpace = 30;
        else
            minYSpace = 15;

        auto localBounds = slider.getLocalBounds();

        auto textBoxWidth = jmax(0, jmin(slider.getTextBoxWidth(), localBounds.getWidth() - minXSpace));
        auto textBoxHeight = jmax(0, jmin(slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));

        Slider::SliderLayout layout;

        // 2. set the textBox bounds

        if (textBoxPos != Slider::NoTextBox)
        {
            if (slider.isBar())
            {
                layout.textBoxBounds = localBounds;
            }
            else
            {
                layout.textBoxBounds.setWidth(textBoxWidth);
                layout.textBoxBounds.setHeight(textBoxHeight);

                if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX(0);
                else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX(localBounds.getWidth() - textBoxWidth);
                else  layout.textBoxBounds.setX((localBounds.getWidth() - textBoxWidth) / 2);

                if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY(0);
                else if (textBoxPos == Slider::TextBoxBelow)     layout.textBoxBounds.setY(localBounds.getHeight() - textBoxHeight);
                else     layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight) / 2);
            }
        }

        // 3. set the slider bounds

        layout.sliderBounds = localBounds;

        if (slider.isBar())
        {
            layout.sliderBounds.reduce(1, 1);   // bar border
        }
        else
        {
            if (textBoxPos == Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft(textBoxWidth);
            else if (textBoxPos == Slider::TextBoxRight) layout.sliderBounds.removeFromRight(textBoxWidth);
            else if (textBoxPos == Slider::TextBoxAbove) layout.sliderBounds.removeFromTop(textBoxHeight);
            else if (textBoxPos == Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom(textBoxHeight);

            const int thumbIndent = getSliderThumbRadius(slider);

            if (slider.isHorizontal())    layout.sliderBounds.reduce(thumbIndent, 0);
            else if (slider.isVertical()) layout.sliderBounds.reduce(0, thumbIndent);
        }

        return layout;
        */
    }
};