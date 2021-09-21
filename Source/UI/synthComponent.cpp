/*
  ==============================================================================

    synthComponent.cpp
    Created: 21 Sep 2021 10:48:55pm
    Author:  cecon

  ==============================================================================
*/

#include <JuceHeader.h>
#include "synthComponent.h"

//==============================================================================
synthComponent::synthComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

synthComponent::~synthComponent()
{
}

void synthComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("synthComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void synthComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
