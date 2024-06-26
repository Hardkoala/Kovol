/*
  ==============================================================================

    Oscillator.h
    Created: 5 Jun 2024 12:05:35pm
    Author:  valen

  ==============================================================================
*/

#pragma once

const float TWO_PI= 6.2831853071795864f;

class Oscillator3{
    public:
        float amplitude;
        //float freq;
        //float sampleRate;
        //float phaseOffset;
        //int sampleIndex;
        float inc;
        float phase;
        
        void reset(){
            
            //sampleIndex=0;
            phase=0.0f;
            
            sin0=amplitude*std::sin(phase * TWO_PI);
            sin1=amplitude*std::sin((phase-inc) * TWO_PI);
            dsin=2.0f*std::cos(inc*TWO_PI);
            
        }
        
        /*float nextSample(){
            //float output=amplitude*std::sin(TWO_PI* sampleIndex*freq /sampleRate+phaseOffset);
            //sampleIndex +=1;
            //return output;
            phase+= inc;
            if(phase >= 1.0f){
                phase -=1.0f;
            }
            return amplitude*std::sin(TWO_PI * phase);
        }*/
    
        float nextSample(){
            float sinx= dsin*sin0-sin1;
            sin1=sin0;
            sin0=sinx;
            return sinx;
            
    }
    private:
        float sin0;
        float sin1;
        float dsin;
    
    
};
