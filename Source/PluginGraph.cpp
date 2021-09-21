/*
  ==============================================================================

    PluginGraph.cpp
    Created: 21 Sep 2021 10:42:46pm
    Author:  cecon

  ==============================================================================
*/

#include "PluginGraph.h"

void PluginGraph::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    isPrepared = true;
}

void PluginGraph::releaseResources()
{

}

void PluginGraph::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
}

void PluginGraph::updateSynthPararms(const float freq, const float gain, const float cutoff, const bool gate)
{
    fSynth.setFreq(freq);
    fSynth.setGain(gain);
    fSynth.setCutoff(cutoff);
    fSynth.setGate(gate);
}

void PluginGraph::updateEffectParams(const float delay, const float feedback)
{
    fEffect.setDelay(delay);
    fEffect.setFeedback(feedback);
}