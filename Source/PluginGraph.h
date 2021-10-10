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
    using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
    using Node = juce::AudioProcessorGraph::Node;

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, juce::MidiBuffer& midiMessages);

    void updateSynthPararms(const float freq, const float gain, const float cutoff, const bool gate);
    void updateEffectParams(const float delay, const float feedback);

private:
    synthDSP fSynth;
    effectDSP fEffect;

    void initialiseGraph();
    void connectAudioNodes();
    void connectMidiNodes();

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;

    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;

    Node::Ptr synthOutputNode;
    Node::Ptr effectInputNode;
    Node::Ptr effectOutputNode;

    bool isPrepared{ false };
};