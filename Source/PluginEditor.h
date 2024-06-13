/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RotatoryKnob.h"
#include "LookAndFeel.h"

//==============================================================================
/**
*/
class KOSCAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KOSCAudioProcessorEditor (KOSCAudioProcessor&);
    ~KOSCAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override; // paints contents of the UI
    void resized() override; //layout of the contents. Will position knobs, etc inside editor window

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KOSCAudioProcessor& audioProcessor;
    
    
    using APVTS=juce::AudioProcessorValueTreeState;
    using SliderAttachment=APVTS::SliderAttachment;
    using ButtonAttchment=APVTS::ButtonAttachment;
    
    LookAndFeel globalLNF;
    
    //juce::Slider outputLevelKnob;
    RotatoryKnob outputLevelKnob;
    SliderAttachment outputLevelAttachment {audioProcessor.apvts, ParameterID::outputLevel.getParamID(), outputLevelKnob.slider};
    
    //juce::Slider noiseKnob;
    RotatoryKnob noiseKnob;
    SliderAttachment noiseAttachment {audioProcessor.apvts, ParameterID::noise.getParamID(), noiseKnob.slider};
    
    juce::TextButton polyModeButton;
    ButtonAttchment polyModerAttachment{audioProcessor.apvts, ParameterID::polyMode.getParamID(), polyModeButton};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KOSCAudioProcessorEditor)
};
