/*
  ==============================================================================

    UIPanel.h
    Created: 2 Jun 2024 5:03:52pm
    Author:  USER

  ==============================================================================
*/

#include <JuceHeader.h>

#pragma once
class Panel 
{
public:
    Panel(int x, int y, int width, int height, juce::String title);
    void paint(juce::Graphics& g);

    juce::String panelTitle;
    int x = 0; 
    int y = 0;
    int width = 0;
    int height = 0;

private:
    static const juce::Font getSpaceMono();
};