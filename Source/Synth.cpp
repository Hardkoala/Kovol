/*
  ==============================================================================

    Synth.cpp

  ==============================================================================
*/

#include "Synth.h"

Synth::Synth(){
    sampleRate=44100.0f;
}

void Synth::allocateResources(double sampleRate_, int /*samplesPerBlock*/){
    sampleRate=static_cast<float>(sampleRate_);
    
}

void Synth::deallocateResources(){
    // do nothing
}

void Synth::reset(){
    voice.reset();
    noiseGen.reset();
    outputLevelSmoother.reset(sampleRate, 0.05);
}
//--------------------------------------------------------------------------------------
//NOTE ON:

/* Chap4:
 void Synth::noteOn(int note, int velocity){
    voice.note=note;
    
    //voice.velocity=velocity;
    voice.osc.amplitude=(velocity/127.0f)*0.5f; //*0.05f we decrease amplitude, so its not annoying
    voice.osc.freq=15000;
    voice.osc.sampleRate=sampleRate;
    voice.osc.phaseOffset=0.0f;
    voice.osc.reset();
    
}*/

//--------------------------------------------------------------------------------------
//NOTE ON and NOTE OFF:
//--------------------------------------------------------------------------------------



void Synth::noteOn(int note, int velocity){
    
    voice.note=note;
    
    float freq=440.0f * std::exp2(float(note-69)/12.0f);
    
    voice.osc.amplitude=(velocity/127.0f)*0.5f;
    voice.osc.inc=freq/sampleRate;
    voice.osc.reset();
}



//Note OFF:
void Synth::noteOff(int note){
    if(voice.note==note){
        voice.note=0;
        //voice.velocity=0;
    }
}



//--------------------------------------------------------------------------------------
//RENDER AUDIO:
//--------------------------------------------------------------------------------------


void Synth::render(float** outputBuffers, int sampleCount){
    
    float* outputBufferLeft=outputBuffers[0];
    float* outputBufferRight=outputBuffers[1];
    
    //1-Loop through the sample sin the buffer one-by-one. sampleCount is number of samples to render.
    //If there are MIDI, sampleCount will be less than num of samples in block
    for (int sample=0; sample<sampleCount; ++sample){
        //2 next output from noiseGen
        
        float noise=noiseGen.nextValue()* noiseMix;
        float output=0.0f;
        //float outputLeft=0.0f;
        //float outputRight=0.0f;
        
        
        if(voice.note>0){
            //output=noise*(voice.velocity/127.0f)*0.5f;
            output=voice.render() +noise;
        }
        
     
        float outputLevel = outputLevelSmoother.getNextValue();
        output *= outputLevel;
        
        
        outputBufferLeft[sample]=output;
        if(outputBufferRight!=nullptr){
            outputBufferRight[sample]=output;
        }
    }
    protectYourEars(outputBufferLeft, sampleCount);
    protectYourEars(outputBufferRight, sampleCount);
}




//--------------------------------------------------------------------------------------
//MIDI MESSAGES:
//--------------------------------------------------------------------------------------


void Synth::midiMessage(uint8_t data0, uint8_t data1, uint8_t data2){
    
    switch (data0 & 0xF0){
            
            //NoteOFF
        case 0x80: //if command is 0x80: NoteOFF
            noteOff(data1 & 0x7F);
            break;
            
            //NoteON:
        case 0x90:{ //if command is 0x80: NoteON
            uint8_t note = data1 & 0x7F;
            uint8_t velo = data2 & 0x7F;
            if(velo>0){
                noteOn(note, velo);
            } else{
                noteOff(note);
            }
            break;
        }
    }
    
}





