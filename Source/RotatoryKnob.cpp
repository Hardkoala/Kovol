/*
  ==============================================================================

    RotatoryKnob.cpp
    Created: 10 Jun 2024 11:22:10pm
    Author:  valen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RotatoryKnob.h"

//==============================================================================

static constexpr int labelHeight=15;
static constexpr int textBoxHeight=20;

RotatoryKnob::RotatoryKnob(){
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, textBoxHeight);
    addAndMakeVisible(slider);
    
    setBounds(0,0,100,120);
    
    slider.setRotaryParameters(juce::degreesToRadians(225.0f), juce::degreesToRadians(495.05), true);
    

}

RotatoryKnob::~RotatoryKnob()
{
}

void RotatoryKnob::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    
    g.setFont (15.0f);
    g.setColour (juce::Colours::white);
    
    auto bounds=getLocalBounds();
    g.drawText(label, juce::Rectangle<int>{0, 0, bounds.getWidth(), labelHeight}, juce::Justification::centred);
    
    /*
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds(), 1);
    
    g.setColour(juce::Colours::yellow);
    g.drawRect(0,labelHeight, bounds.getWidth(),bounds.getHeight()-labelHeight-textBoxHeight, 1);
    
    g.setColour(juce::Colours::green);
    g.drawRect(0,0, bounds.getWidth(), labelHeight,1);*/
    
    
}
    


void RotatoryKnob::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds=getLocalBounds();
    slider.setBounds(0, labelHeight, bounds.getWidth(), bounds.getHeight()-labelHeight);

}
