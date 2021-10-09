/*
  ==============================================================================

    synthDSP.cpp
    Created: 21 Sep 2021 10:48:17pm
    Author:  cecon

  ==============================================================================
*/

#include "synthDSP.h"
#include "faustDSP/FaustSynth.h"

void synthDSP::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    fDSP = new mydsp();
    fDSP->init(sampleRate);
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    outputs = new float* [2];
    for (int channel = 0; channel < 2; ++channel)
    {
        outputs[channel] = new float[samplesPerBlock];
    }
}

void synthDSP::releaseResources()
{
    delete fDSP;
    delete fUI;
    for (int channel = 0; channel < 2; ++channel)
    {
        delete[] outputs[channel];
    }
    delete[] outputs;
}

void synthDSP::getNextAudioBlock(juce::AudioBuffer<float>& block)
{
    fDSP->compute(block.getNumSamples(), NULL, outputs);

    for (int channel = 0; channel < 2; channel++)
    {
        for (int sample = 0; sample < block.getNumSamples(); sample++)
        {
            *block.getWritePointer(channel, sample) = outputs[channel][sample];
        }
    }
}

void synthDSP::setFreq(float freq)
{
    fUI->setParamValue("freq", freq);
}

void synthDSP::setGain(float gain)
{
    fUI->setParamValue("gain", gain);
}

void synthDSP::setCutoff(float cutoff)
{
    fUI->setParamValue("cutoff", cutoff);
}

void synthDSP::setGate(bool gate)
{
    if (gate)
    {
        fUI->setParamValue("gate", 1);
    }
    else
    {
        fUI->setParamValue("gate", 0);
    }
}
