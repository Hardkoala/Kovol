/*
  ==============================================================================

 Oscillator.h

  ==============================================================================
*/

#pragma once

class Oscillator{
    
public:
    float amplitude;
    float inc;
    float phase;
    
    void reset(){
        phase=0.0f;
    }
    
    float nextSample(){
        phase += inc;
        if(phase >= 1.0f){
            phase -= 1.0f;
        }
        return amplitude * (2.0f*phase - 1.0f);
    }
};
