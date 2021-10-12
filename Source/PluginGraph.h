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
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, juce::MidiBuffer& midiMessages);

    void updateSynthPararms(const float freq, const float gain, const float cutoff, const bool gate);
    void updateEffectParams(const float delay, const float feedback);

private:
    synthDSP fSynth;
    effectDSP fEffect;

    juce::AudioBuffer<float> synthOut;
    juce::AudioBuffer<float> effectIn;
    juce::AudioBuffer<float> effectOut;

    int writePosition{ 0 };

    bool isPrepared{ false };
};