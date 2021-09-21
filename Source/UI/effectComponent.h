/*
  ==============================================================================

    effectComponent.h
    Created: 21 Sep 2021 10:48:41pm
    Author:  cecon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class effectComponent  : public juce::Component
{
public:
    effectComponent();
    ~effectComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (effectComponent)
};
