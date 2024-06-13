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
    
    //outputLevelKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //outputLevelKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    outputLevelKnob.label="Level";
    addAndMakeVisible(outputLevelKnob);
    
    //noiseKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //noiseKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    
    /* AÑADIR LOGO
    auto image= juce::ImageCache__getFromMemory(BinaryData::Logo_png, BinaryData::Logo_pngSize);
    graphics.drawImage(image, ........)*/

    
}

//==============================================================================
//RESIZED
//==============================================================================

void KOSCAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //outputLevelKnob.setBounds(20, 20, 100, 200);
    //noiseKnob.setBounds(120,20,100,120);
    juce::Rectangle r(20, 20, 200, 220);
    outputLevelKnob.setBounds(r);
    
    r=r.withX(r.getRight()+20);
    noiseKnob.setBounds(r);
    
    polyModeButton.setSize(80,30);
    polyModeButton.setCentrePosition(r.withX(r.getRight()).getCentre());
}
