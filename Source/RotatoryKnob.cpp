/*
  ==============================================================================

    RotatoryKnob.cpp

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
    // This demo code just fills the component's background and draws some placeholder text to get you started.
     

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    
    g.setFont (15.0f);
    g.setColour (juce::Colours::white);
    
    auto bounds=getLocalBounds();
    g.drawText(label, juce::Rectangle<int>{0, 0, bounds.getWidth(), labelHeight}, juce::Justification::centred);
    
}
    


void RotatoryKnob::resized()
{
    // Set the bounds of any child components that your component contains..
    
    auto bounds=getLocalBounds();
    slider.setBounds(0, labelHeight, bounds.getWidth(), bounds.getHeight()-labelHeight);
}
