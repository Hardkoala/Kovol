/*
  ==============================================================================

    OsciDemo.cpp

  ==============================================================================
*/

#include "OsciDemo.h"

OsciDemo::OsciDemo() { //es necesario que se inicialice aqui¿?
    
    phase = 0.0f;
    rectThreshold = 0.5f;
    rectGain = 1.0f;
    compThreshold = 0.0f;
    compGain = 0.0f;
}
void OsciDemo::reset() {
    phase = 0.0f;
    
    rectThreshold = 0.5f;
    rectGain = 1.0f;
    compThreshold = 0.0f;
    compGain = 0.0f;
}



void OsciDemo::setWaveformParameters(float value) {
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



/*float OsciDemo::comparator(float inputSample, float threshold) {
    return (inputSample > threshold) ? 1.0f : -1.0f;*/
    
float OsciDemo::comparator (float inputSample, float threshold) {
    float outputSample;
    if (inputSample > threshold) {
        outputSample = 1.0f;
    } else {
        outputSample = -1.0f;
    }
    return outputSample;
}


/*float OsciDemo::rectifier(float inputSample, float threshold) {
    float outputSample = (inputSample <= threshold) ? inputSample : threshold - inputSample;
    return outputSample + (1.0f - threshold) / 2.0f;
}*/

float OsciDemo::rectifier(float inputSample, float threshold) {
    float outputSample;
    if (inputSample <= threshold) {
        outputSample = inputSample;
    } else {
//        outputSample = threshold - inputSample;
        outputSample =   inputSample -  threshold;
    
    }
        return outputSample + (1.0f - threshold) / 2.0f;
}




float OsciDemo::nextSample(float X) {
 
    setWaveformParameters(X); //AQUI METER WAVEF!
    
    phase += inc;
    
#if INV_SAW==0
    if (phase >= 1.0f) {
        phase -= 1.0f;
    }
    
    float sawtoothSginal = amplitude * (2.0f * phase - 1.0f);  // Sawtooth signal
#else
    
    if (phase >= 1.0f) {
        phase -= 1.0f;
    }
    
    float sawtoothSginal= 1.0f - 2.0f * phase;

#endif
    

    float a = rectifier(sawtoothSginal, rectThreshold); // Apply Rectifier
    a *= rectGain;

    float b = comparator(sawtoothSginal, compThreshold); // Apply Comparator
    b *= compGain;

    return (a + b)/2;
}
