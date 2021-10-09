/*
  ==============================================================================

    synthDSP.h
    Created: 21 Sep 2021 10:48:17pm
    Author:  cecon

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class dsp;
class MapUI;

class synthDSP
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);// , int outputChannels);
    void releaseResources();
    void getNextAudioBlock(juce::AudioBuffer<float>& block);

    void setFreq(float freq);
    void setGain(float gain);
    void setCutoff(float cutoff);
    void setGate(bool gate);

private:
    MapUI* fUI;
    dsp* fDSP;
    float** outputs;

    int lastMidiNote{ 0 };
};