/*
  ==============================================================================

    PluginGraph.h
    Created: 21 Sep 2021 10:42:46pm
    Author:  cecon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DSP/synthDSP.h"
#include "DSP/effectDSP.h"

class PluginGraph
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void releaseResources();
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);

    void updateSynthPararms(const float freq, const float gain, const float cutoff, const bool gate);
    void updateEffectParams(const float delay, const float feedback);

private:
    synthDSP fSynth;
    effectDSP fEffect;

    bool isPrepared{ false };
};