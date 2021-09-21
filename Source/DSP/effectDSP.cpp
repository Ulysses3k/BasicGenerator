/*
  ==============================================================================

    effectDSP.cpp
    Created: 21 Sep 2021 10:48:07pm
    Author:  cecon

  ==============================================================================
*/

#include "effectDSP.h"
#include "faustDSP/FaustEffect.h"

void effectDSP::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    fDSP = new mydsp();
    fDSP->init(sampleRate);
    fUI = new MapUI;
    fDSP->buildUserInterface(fUI);
    inputs = new float* [2];
    outputs = new float* [2];
    for (int channel = 0; channel < 2; ++channel)
    {
        inputs[channel] = new float[samplesPerBlock];
        outputs[channel] = new float[samplesPerBlock];
    }
}

void effectDSP::releaseResources()
{
    delete fDSP;
    delete fUI;
    for (int channel = 0; channel < 2; ++channel)
    {
        delete[] inputs[channel];
        delete[] outputs[channel];
    }
    delete[] inputs;
    delete[] outputs;
}

void effectDSP::getNextAudioBlock(juce::AudioBuffer<float> block)
{
    for (int channel = 0; channel < 2; ++channel)
    {
        for (int sample = 0; sample < block.getNumSamples(); sample++)
        {
            inputs[channel][sample] = *block.getWritePointer(channel, sample);
        }
    }

    fDSP->compute(block.getNumSamples(), inputs, outputs);

    for (int channel = 0; channel < 2; ++channel)
    {
        for (int sample = 0; sample < block.getNumSamples(); sample++)
        {
            *block.getWritePointer(channel, sample) = outputs[channel][sample];
        }
    }
}

void effectDSP::setDelay(float delay)
{
    fUI->setParamValue("delay", delay);
}

void effectDSP::setFeedback(float feedback)
{
    fUI->setParamValue("feedback", feedback);
}