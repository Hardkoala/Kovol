/*
  ==============================================================================

    RotatoryKnob.h
    Created: 10 Jun 2024 11:22:10pm
    Author:  valen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RotatoryKnob  : public juce::Component
{
public:
    
    juce::Slider slider;
    juce::String label;
    
    
    RotatoryKnob();
    ~RotatoryKnob() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotatoryKnob)
};
