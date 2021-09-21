/*
  ==============================================================================

    synthComponent.h
    Created: 21 Sep 2021 10:48:55pm
    Author:  cecon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class synthComponent  : public juce::Component
{
public:
    synthComponent();
    ~synthComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (synthComponent)
};
