/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JohnSynthAudioProcessor::JohnSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(lpFreq = new juce::AudioParameterFloat(
        "lpFreq", 
        "LpFreq",
        20.f, 
        21000.f,
        1200.f
    ));

    addParameter(lpRes = new juce::AudioParameterFloat(
        "lpres",
        "LpRes",
        0.01f,
        1.f,
        0.5f
    ));

    addParameter(hpFreq = new juce::AudioParameterFloat(
        "hpFreq",
        "hpFreq",
        20.f,
        21000.f,
        1200.f
    ));

    addParameter(hpRes = new juce::AudioParameterFloat(
        "hpres",
        "hpRes",
        0.01f,
        1.f,
        0.5f
    ));
}

JohnSynthAudioProcessor::~JohnSynthAudioProcessor()
{
    // you absolute monkey if you put any code here remember that this
    // is the DESTRUCTOR NOT THE CONSTRUCTOR
}

//==============================================================================
const juce::String JohnSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JohnSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JohnSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JohnSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JohnSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JohnSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JohnSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JohnSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JohnSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void JohnSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JohnSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    sawSampler.setup();
    sawSampler.setCurrentPlaybackSampleRate(sampleRate);

    harmSawSampler.transpose = -12;
    harmSawSampler.setup();
    harmSawSampler.setCurrentPlaybackSampleRate(sampleRate);

    widener.outputChannelCount = getTotalNumOutputChannels();
    widener.width = 1.2f;

    juce::dsp::ProcessSpec spec{};
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    spec.sampleRate = sampleRate;
    filter.prepare(spec);

    masterLimiter.prepare(spec); masterLimiter.reset();
    masterLimiter.setRelease(100.f);
    masterLimiter.setThreshold(-6.f);

    masterCompressor.prepare(spec);
    masterCompressor.reset();
    masterCompressor.setAttack(100.f);
    masterCompressor.setRatio(2.f);
    masterCompressor.setRelease(200.f);
    masterCompressor.setThreshold(-18.f);

    harmonyCompressor.prepare(spec); harmonyCompressor.reset();
    harmonyCompressor.setAttack(10.f);
    harmonyCompressor.setRatio(4.f);
    harmonyCompressor.setRelease(100.f);
    harmonyCompressor.setThreshold(-6.f);

    harmonyGain.prepare(spec); harmonyGain.setGainDecibels(-6.f);
    mainGain.prepare(spec); mainGain.setGainDecibels(-6.f);
    masterGain.prepare(spec); masterGain.setGainDecibels(-6.f);

    //lfo.prepare(spec);
    //lfo.setFrequency(600.f);
}

void JohnSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JohnSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JohnSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    kbState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    harmSawSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    harmonyCompressor.process(context);
    harmonyGain.process(context);

    sawSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mainGain.process(context);

    // filter.process(buffer);

    // update filter if the parameters don't match
    if (filter.parametersMatch(*lpFreq, *lpRes, *hpFreq, *hpRes) == false) 
    {
        filter.updateFilters(getSampleRate(), *lpFreq, *lpRes, *hpFreq, *hpRes);
    }

    filter.process(buffer);

    masterGain.process(context);
    masterCompressor.process(context);
    masterLimiter.process(context);

    widener.process(buffer);
}

//==============================================================================
bool JohnSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JohnSynthAudioProcessor::createEditor()
{
    return new JohnSynthAudioProcessorEditor (*this);
}

//==============================================================================
void JohnSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JohnSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JohnSynthAudioProcessor();
}
