/*
  ==============================================================================

    OsciDemo.h


  ==============================================================================
*/

#pragma once

#define INV_SAW 1 //Inverted Sawtooth if INV_SAW==1

class OsciDemo {
public:
    float oscValue;
    
    float amplitude;
    float inc;
    float phase;
    
    OsciDemo();
    void reset();
    void setWaveformParameters(float value);  // Agregar el tipo de dato para el parámetro
    float comparator(float inputSample, float threshold);
    float rectifier(float inputSample, float threshold);
//    float nextSample(float value);  // Agregar el tipo de dato para el parámetro
    float nextSample(float X);
private:

    float rectThreshold;
    float rectGain;
    float compThreshold;
    float compGain;
    const float splitPointA = 0.33f;
    const float splitPointB = 0.66f;
};
