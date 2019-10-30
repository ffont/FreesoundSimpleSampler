/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FreesoundSimpleSamplerAudioProcessor::FreesoundSimpleSamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : 		 AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	tmpDownloadLocation = File::getSpecialLocation(File::userDocumentsDirectory).getChildFile("FreesoundSimpleSampler");
	tmpDownloadLocation.deleteRecursively();
	tmpDownloadLocation.createDirectory();
	midicounter = 1;
	startTime = Time::getMillisecondCounterHiRes() * 0.001;
}

FreesoundSimpleSamplerAudioProcessor::~FreesoundSimpleSamplerAudioProcessor()
{
    // Deletes the tmp directory so downloaded files do not stay there
    tmpDownloadLocation.deleteRecursively();
	for (int i = 0; i < downloadTasksToDelete.size(); i++) {
	
		delete downloadTasksToDelete.at(i);
	
	}
}

//==============================================================================
const String FreesoundSimpleSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FreesoundSimpleSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FreesoundSimpleSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FreesoundSimpleSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FreesoundSimpleSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FreesoundSimpleSamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FreesoundSimpleSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FreesoundSimpleSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const String FreesoundSimpleSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void FreesoundSimpleSamplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FreesoundSimpleSamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	sampler.setCurrentPlaybackSampleRate(sampleRate);

	
}

void FreesoundSimpleSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	


}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FreesoundSimpleSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void FreesoundSimpleSamplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	midiMessages.addEvents(midiFromEditor, 0, -1, 0);
	midiFromEditor.clear();
	sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	
}

//==============================================================================
bool FreesoundSimpleSamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FreesoundSimpleSamplerAudioProcessor::createEditor()
{
    return new FreesoundSimpleSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void FreesoundSimpleSamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FreesoundSimpleSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void FreesoundSimpleSamplerAudioProcessor::newSoundsReady (Array<FSSound> sounds)
{
    // This method is called by the FreesoundSearchComponent when a new query has
    // been made and new sounda have been selected for loading into the sampler.
    // This methods downloads the sounds, sotres in tmp directory and...
    
    // Download the sounds
    
    std::cout << "Downloading new sounds" << std::endl;
    FreesoundClient client(FREESOUND_API_KEY);
    for (int i=0; i<sounds.size(); i++){
        File location = tmpDownloadLocation.getChildFile(sounds[i].id).withFileExtension("mp3");
        std::cout << location.getFullPathName() << std::endl;
		URL::DownloadTask* downloadTask = client.downloadMP3SoundPreview(sounds[i], location);
		downloadTasksToDelete.push_back(downloadTask);
    }

	setSources();
}

void FreesoundSimpleSamplerAudioProcessor::setSources()
{
	int poliphony = 16;
	int maxLength = 10;
	for (int i = 0; i < poliphony; i++) {
		sampler.addVoice(new SamplerVoice());
	}

	audioFormatManager.registerBasicFormats();

	Array<File> files = tmpDownloadLocation.findChildFiles(2, false);
	for (int i = 0; i < files.size(); i++) {
		std::unique_ptr<AudioFormatReader> reader(audioFormatManager.createReaderFor(files[i]));
		BigInteger notes;
		notes.setRange(i * 8, i * 8 + 7, true);
		sampler.addSound(new SamplerSound(String(i), *reader, notes, i*8, 0, maxLength, maxLength));
		//reader.release();
	}


}

void FreesoundSimpleSamplerAudioProcessor::addToMidiBuffer(int notenumber)
{

	MidiMessage message = MidiMessage::noteOn(10, notenumber, (uint8)100);
	double timestamp = Time::getMillisecondCounterHiRes() * 0.001 - getStartTime();
	message.setTimeStamp(timestamp);

	auto sampleNumber = (int)(timestamp * getSampleRate());

	midiFromEditor.addEvent(message,sampleNumber);

	auto messageOff = MidiMessage::noteOff(message.getChannel(), message.getNoteNumber());
	messageOff.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001 - startTime);
	midiFromEditor.addEvent(messageOff,sampleNumber+1);

}

double FreesoundSimpleSamplerAudioProcessor::getStartTime(){
	return startTime;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FreesoundSimpleSamplerAudioProcessor();
}




