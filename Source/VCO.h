/*
  ==============================================================================

    vco.h
    Created: 9 Jun 2024 7:15:40pm
    Author:  valen

  ==============================================================================
*/

#pragma once
#include "Rectifier.h"
#include "Comparator.h"

class VCO {
public:
    VCO()
        : splitPointA(0.3f), splitPointB(0.6f), amplitude(1.0f), inc(0.01f), phase(0.0f)
    {}

    void setWaveformParameters(float value) {
        if (value < splitPointA) {
            compGain = 0.0f;
            rectGain = 1.0f;
            compThreshold = 0.0f;
            rectThreshold = value / splitPointA;
        } else if (value < splitPointB) {
            compThreshold = 0.0f;
            float currentSplitPosition = (value - splitPointA) / (splitPointB - splitPointA);
            compGain = currentSplitPosition;
            rectGain = 1.0f - currentSplitPosition;
            rectThreshold = 1.0f;
        } else {
            compGain = 1.0f;
            rectGain = 0.0f;
            float currentSplitPosition = (value - splitPointB) / (1.0f - splitPointB);
            compThreshold = currentSplitPosition;
            rectThreshold = 1.0f;
        }
    }

    void reset() {
        phase = 0.0f;
    }

    float nextSample(float value) {
        phase += inc;
        if (phase >= 1.0f) {
            phase -= 1.0f;
        }
        setWaveformParameters(value);
        
        y = amplitude * (2.0f * phase - 1.0f);

        float a = rectifier.processSample(y, rectThreshold);
        a = a * rectGain;

        float b = comparator.processSample(y, compThreshold);
        b = b * compGain;

        return a + b;
    }

private:
    Rectifier rectifier;
    Comparator comparator;

    float splitPointA;
    float splitPointB;

    float compGain = 0.0f;
    float rectGain = 1.0f;
    float compThreshold = 0.0f;
    float rectThreshold = 0.0f;

    float amplitude;
    float inc;
    float phase;
    float y;
    float a;
    float b;
};




