/*
  ==============================================================================

    Width.h
    Created: 31 May 2024 11:24:45pm
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Widener 
{
public:
    int outputChannelCount;
    float width;

    void process(juce::AudioBuffer<float> buffer) 
    {
        for (int channel = 0; channel < outputChannelCount; ++channel)
        {
            auto* outLeft = buffer.getWritePointer(0);
            auto* outRight = buffer.getWritePointer(1);

            auto scalarCoefficient = width * .5f;

            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                auto inLeft = outLeft[sample];
                auto inRight = outRight[sample];

                auto m = (inLeft + inRight) * .5f;
                auto s = (inRight - inLeft) * scalarCoefficient;

                outLeft[sample] = m - s;
                outRight[sample] = m + s;
            }
        }
    }
};