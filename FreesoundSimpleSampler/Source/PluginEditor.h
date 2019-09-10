/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "FreesoundSearchComponent.h"

//==============================================================================
/**
*/
class FreesoundSimpleSamplerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    FreesoundSimpleSamplerAudioProcessorEditor (FreesoundSimpleSamplerAudioProcessor&);
    ~FreesoundSimpleSamplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FreesoundSimpleSamplerAudioProcessor& processor;
    
    FreesoundSearchComponent freesoundSearchComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreesoundSimpleSamplerAudioProcessorEditor)
};
