/*
  ==============================================================================

    UIPanel.cpp
    Created: 2 Jun 2024 5:03:52pm
    Author:  USER

  ==============================================================================
*/

#include "UIPanel.h"

Panel::Panel(int x, int y, int width, int height, juce::String title)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->panelTitle = title;
}

void Panel::paint(juce::Graphics& g)
{
    juce::Image panel = juce::ImageCache::getFromMemory(BinaryData::empty_panel_png, BinaryData::empty_panel_pngSize);
    g.drawImageWithin(panel, x, y, width, height, false);

    g.setFont(getSpaceMono());
    g.setFont(22.f);
    g.setColour(juce::Colours::black);
    g.drawText(panelTitle, x, y + 1, width, 20, juce::Justification::centred, false);
}

const juce::Font Panel::getSpaceMono()
{
    static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::SpaceMonoRegular_ttf, BinaryData::SpaceMonoRegular_ttfSize);
    return typeface;
}