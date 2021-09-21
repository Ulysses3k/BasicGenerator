/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicGeneratorAudioProcessor::BasicGeneratorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
}

BasicGeneratorAudioProcessor::~BasicGeneratorAudioProcessor()
{
}

//==============================================================================
const juce::String BasicGeneratorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicGeneratorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicGeneratorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicGeneratorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicGeneratorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicGeneratorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicGeneratorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicGeneratorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasicGeneratorAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicGeneratorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasicGeneratorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    graph.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void BasicGeneratorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicGeneratorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicGeneratorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // SYNTH
    auto& freq = *apvts.getRawParameterValue("FREQ");
    auto& gain = *apvts.getRawParameterValue("GAIN");
    auto& cutoff = *apvts.getRawParameterValue("CUTOFF");
    auto& gate = *apvts.getRawParameterValue("GATE");

    // EFFECT


    graph.updateSynthPararms(freq, gain, cutoff, gate);

    graph.renderNextBlock(buffer, 0, buffer.getNumSamples());
}

//==============================================================================
bool BasicGeneratorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasicGeneratorAudioProcessor::createEditor()
{
    return new BasicGeneratorAudioProcessorEditor (*this);
}

//==============================================================================
void BasicGeneratorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicGeneratorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicGeneratorAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout BasicGeneratorAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // SYNTH PARAMS
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FREQ",
        "Frequency",
        juce::NormalisableRange<float>{200.0f, 5000.0f, 0.1f, 0.6f},
        500.0f
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "GAIN",
        "Gain",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f},
        0.3f
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "CUTOFF",
        "Cutoff",
        juce::NormalisableRange<float>{20.0f, 20000.0f, 0.1f, 0.6f},
        1000.0f
        ));

    params.push_back(std::make_unique<juce::AudioParameterBool>(
        "GATE",
        "Gate",
        false
        ));

    // EFFECT PARAMS
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "DELAY",
        "Delay",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f},
        0.5f
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FEEDBACK",
        "Feedback",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f},
        0.5f
        ));

    return { params.begin(), params.end() };
}