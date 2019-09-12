/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FreesoundSimpleSamplerAudioProcessorEditor::FreesoundSimpleSamplerAudioProcessorEditor (FreesoundSimpleSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    freesoundSearchComponent.setProcessor(&processor);
    addAndMakeVisible (freesoundSearchComponent);

    setSize (10, 10);  // Is re-set when running resize()
    setResizable(false, false);
}

FreesoundSimpleSamplerAudioProcessorEditor::~FreesoundSimpleSamplerAudioProcessorEditor()
{
}

//==============================================================================
void FreesoundSimpleSamplerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void FreesoundSimpleSamplerAudioProcessorEditor::resized()
{
    float width = 800;
    float height = 450;
    float unitMargin = 10;
    
    freesoundSearchComponent.setBounds (unitMargin,  unitMargin, (width / 2) - (unitMargin / 2), height - 2 * unitMargin);
    
    setSize(width, height);
}
