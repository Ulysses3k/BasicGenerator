/*
  ==============================================================================

    PluginGraph.cpp
    Created: 21 Sep 2021 10:42:46pm
    Author:  cecon

  ==============================================================================
*/

#include "PluginGraph.h"

void PluginGraph::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synthOut.setSize(2, samplesPerBlock, false, false, true);
    effectIn.setSize(2, samplesPerBlock, false, false, true);
    effectOut.setSize(2, samplesPerBlock, false, false, true);

    fSynth.prepareToPlay(sampleRate, samplesPerBlock);
    fEffect.prepareToPlay(sampleRate, samplesPerBlock);

    isPrepared = true;
}

void PluginGraph::releaseResources()
{
    fSynth.releaseResources();
    fEffect.releaseResources();
}

void PluginGraph::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, juce::MidiBuffer& midiMessages)
{
    jassert(isPrepared);

    /*
    outputBuffer.clear();
    synthOut.clear();
    effectIn.clear();
    effectOut.clear();
        
    fSynth.getNextAudioBlock(synthOut);

    for (int channel = 0; channel < 2; ++channel)
    {
        for (int sample = 0; sample < outputBuffer.getNumSamples(); ++sample)
        {
            *outputBuffer.getWritePointer(channel, sample) = *synthOut.getReadPointer(channel, sample);
        }
    }
    */


    fEffect.getNextAudioBlock(outputBuffer);
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