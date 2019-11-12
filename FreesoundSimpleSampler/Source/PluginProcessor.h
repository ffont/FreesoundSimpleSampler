/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FreesoundAPI.h"

//==============================================================================
/**
*/




class FreesoundSimpleSamplerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    FreesoundSimpleSamplerAudioProcessor();
    ~FreesoundSimpleSamplerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    File tmpDownloadLocation;
    void newSoundsReady (Array<FSSound> sounds);

	void setSources();
	void addToMidiBuffer(int notenumber);

	double getStartTime();



private:

	std::vector<URL::DownloadTask*> downloadTasksToDelete;
	Synthesiser sampler;
	AudioFormatManager audioFormatManager;
	MidiBuffer midiFromEditor;
	long midicounter;
	double startTime;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreesoundSimpleSamplerAudioProcessor)
};
