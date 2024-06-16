/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
//Constructor
//==============================================================================
KOSCAudioProcessorEditor::KOSCAudioProcessorEditor (KOSCAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    

    outputLevelKnob.label="Level";
    addAndMakeVisible(outputLevelKnob);
    

    noiseKnob.label="Noise";
    addAndMakeVisible(noiseKnob);
    
    polyModeButton.setButtonText("Poly");
    polyModeButton.setClickingTogglesState(true);
    addAndMakeVisible(polyModeButton);
    
    juce::LookAndFeel::setDefaultLookAndFeel(&globalLNF);
    
    setSize (600, 400);
}

KOSCAudioProcessorEditor::~KOSCAudioProcessorEditor()
{
}


//==============================================================================
//PAINT
//==============================================================================

void KOSCAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Component is opaque, so we must completely fill the background with a solid colour)
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

//==============================================================================
//RESIZED
//==============================================================================

void KOSCAudioProcessorEditor::resized()
{
 
    juce::Rectangle r(20, 20, 200, 220);
    outputLevelKnob.setBounds(r);
    
    r=r.withX(r.getRight()+20);
    noiseKnob.setBounds(r);
    
    polyModeButton.setSize(80,30);
    polyModeButton.setCentrePosition(r.withX(r.getRight()).getCentre());
}
