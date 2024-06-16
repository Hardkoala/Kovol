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
//NOTE ON and NOTE OFF:
//--------------------------------------------------------------------------------------
//NoteOn
void Synth::noteOn(int note, int velocity){
    
    voice.note=note;
    
    float freq=440.0f * std::exp2(float(note-69)/12.0f);
    
    /*voice.osc.amplitude=(velocity/127.0f)*0.5f;
    voice.osc.inc=freq/sampleRate;
    voice.osc.reset();*/
    
    //esta bien¿?
    voice.osc2.amplitude=(velocity/127.0f)*0.5f;
    voice.osc2.inc=freq/sampleRate;
    voice.osc2.reset();
}


//NoteOFF:
void Synth::noteOff(int note){
    if(voice.note==note){
        voice.note=0;
    }
}


//--------------------------------------------------------------------------------------
//RenderAudio:
//--------------------------------------------------------------------------------------
void Synth::render(float** outputBuffers, int sampleCount){
    
    float* outputBufferLeft=outputBuffers[0];
    float* outputBufferRight=outputBuffers[1];
    
    //1-Loop through the sample sin the buffer one-by-one. sampleCount is number of samples to render.
    //If there are MIDI, sampleCount will be less than num of samples in block
    for (int sample=0; sample<sampleCount; ++sample){
        
        float noise=noiseGen.nextValue()* noiseMix;
        float output=0.0f;
        //Habría que añadir waveF¿?
 
        voice.X=X;
        
        if(voice.note>0){
            output=voice.render() + noise;
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
//MidiMessage:
//--------------------------------------------------------------------------------------
void Synth::midiMessage(uint8_t data0, uint8_t data1, uint8_t data2){
    
    switch (data0 & 0xF0){
            
        //NoteOFF: if command is 0x80
        case 0x80:
            noteOff(data1 & 0x7F);
            break;
            
        //NoteON: if command is 0x80
        case 0x90:{
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
