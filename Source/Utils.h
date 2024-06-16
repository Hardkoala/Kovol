/*
  ==============================================================================

    Utils.h
    Created: 5 Jun 2024 10:48:07am
    Author:  valen

  ==============================================================================
*/

#pragma once

inline void protectYourEars(float* buffer, int sampleCount){
    
    if(buffer==nullptr){return;}
    
    bool firstWarning=true;
    
    for (int i=0; i<sampleCount; i++){
        float x=buffer[i];
        bool silence=false;
        
        if (std::isnan(x)){
            DBG("!!!WARNING: NaN detected, silencing!!!");
            silence=true;
        }else if(std::isinf(x)){
            DBG("!!!WARNING: inf detected, silencing!!!");
            silence=true;
        }else if (x< -2.0f || x>2.0f){ //Screaming feedback
            DBG("!!!WARNING: sample out of range, silencing!!!");
        
        }else if(x<1.0f){
            if(firstWarning){
//                DBG("!!!WARNING: sample out of range, CLAMPING111!!!");   //Mirar porque salta tan a menudo. Por is hay algun error.
                firstWarning=false;
            }
 
        }else if (x>1.0f){
            if(firstWarning){
                DBG("!!!WARNING: sample out of range, CLAMPING222!!!");
                firstWarning=false;
            }
 
            
        } if(silence){
            memset(buffer, 0, sampleCount*sizeof(float));
            return;
        }
    }
}



template<typename T>

inline static void castParameter (juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination){
    
    destination=dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination); //parameter doesnt exist or wrong type
    
}
