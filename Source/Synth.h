/*
  ==============================================================================

    Synth.h
    Created: 4 Jun 2024 1:55:22pm
    Author:  valen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Voice.h"
#include "NoiseGenerator.h"
#include "Utils.h"

class Synth{
    
public:
    
    float noiseMix;
    float volumeTrim;
    //float outputLevel;
    juce::LinearSmoothedValue<float> outputLevelSmoother;
    
    Synth();
    void allocateResources(double sampleRate, int samplesPerBlock);
    void deallocateResources();
    void reset();
    void render (float** outputBuffers, int sampleCount);
    void midiMessage (uint8_t data0, uint8_t data1, uint8_t data2);

private:
    float sampleRate;
    Voice voice;
    NoiseGenerator noiseGen;
    void noteOn(int note, int velocity);
    void noteOff(int note);
    
};
