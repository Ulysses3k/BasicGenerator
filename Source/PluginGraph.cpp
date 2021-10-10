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
    mainProcessor->setPlayConfigDetails((int)0, (int)2, sampleRate, samplesPerBlock);
    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);

    //fSynth.prepareToPlay(sampleRate, samplesPerBlock);
    //fEffect.prepareToPlay(sampleRate, samplesPerBlock);

    initialiseGraph();

    isPrepared = true;
}

void PluginGraph::releaseResources()
{
    //fSynth.releaseResources();
    //fEffect.releaseResources();

    mainProcessor->releaseResources();
}

void PluginGraph::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, juce::MidiBuffer& midiMessages)
{
    jassert(isPrepared);

    mainProcessor->processBlock (outputBuffer, midiMessages);

    //fSynth.getNextAudioBlock(outputBuffer);
    //fEffect.getNextAudioBlock(outputBuffer);
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

void PluginGraph::initialiseGraph()
{
    mainProcessor->clear();

    audioOutputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioOutputNode));
    synthOutputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioOutputNode));
    effectInputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioInputNode));
    effectOutputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioOutputNode));

    midiInputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::midiInputNode));

    connectAudioNodes();
    connectMidiNodes();
}

void PluginGraph::connectAudioNodes()
{
    for (int channel = 0; channel < 2; ++channel)
    {
        mainProcessor->addConnection({ {synthOutputNode->nodeID, channel},{effectInputNode->nodeID, channel} });
        mainProcessor->addConnection({ {effectOutputNode->nodeID, channel},{audioOutputNode->nodeID, channel} });
    }
        
    
}

void PluginGraph::connectMidiNodes()
{

}