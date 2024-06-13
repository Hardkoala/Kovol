/*
  ==============================================================================

    Voice.h
    Created: 4 Jun 2024 1:55:37pm
    Author:  valen

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include "Oscillator3.h"
#include "VCO.h"
/*
struct Voice{
    void reset(){
        //do nothing yet
    }
};*/

struct Voice
{
    int note;
    int velocity; //QUITAR!!
    //VCO vco;
    Oscillator osc;
    
    void reset(){
        note=0;
        velocity=0; //QUITAR!!
        osc.reset();
    }
    float render(){
        return osc.nextSample();
        //return vco.nextSample();

        
    }
};


    

