/*
  ==============================================================================

    Voice.h

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include "OsciDemo.h"


struct Voice
{
    int note;
    int velocity; //QUITAR!!
    Oscillator osc;
    OsciDemo osc2;
    
    float X;
    
    
    void reset(){
        note=0;
        velocity=0; //QUITAR!!
        osc.reset();
        osc2.reset();
    }
    
    
    float render(){
        //return osc.nextSample();
        //return osc2.nextSample(osc2.oscValue);// no se si esta bien. el puñetero value!!
        return osc2.nextSample(X);
    }
};
