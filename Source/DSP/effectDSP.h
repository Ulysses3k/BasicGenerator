/*
  ==============================================================================

    effectDSP.h
    Created: 21 Sep 2021 10:48:07pm
    Author:  cecon

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class dsp;
class MapUI;

class effectDSP
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);// , int outputChannels);
    void releaseResources();
    void getNextAudioBlock(juce::AudioBuffer<float>& block);

    void setDelay(float delay);
    void setFeedback(float feedback);

private:
    MapUI* fUI;
    dsp* fDSP;
    float** inputs;
    float** outputs;

};