/*
  ==============================================================================

    FreesoundSearchComponent.h
    Created: 10 Sep 2019 5:44:51pm
    Author:  Frederic Font Corbera

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "api_key.h"


class ResultsTableComponent : public Component, public TableListBoxModel {
public:
    ResultsTableComponent() {
    
        table.setModel(this);
    
        addAndMakeVisible (table);
        
        table.getHeader().addColumn("Name", 1, 200, 50, 1000, (TableHeaderComponent::visible | TableHeaderComponent::resizable ));
        table.getHeader().addColumn("Author", 2, 100, 50, 1000, (TableHeaderComponent::visible | TableHeaderComponent::resizable ));
        table.getHeader().addColumn("License", 3, 400, 50, 1000, (TableHeaderComponent::visible | TableHeaderComponent::resizable ));
    }
    
    int getNumRows() override {
        return (int)data.size();
    }
    
    void paintRowBackground (Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override
    {
        auto alternateColour = getLookAndFeel().findColour (ListBox::backgroundColourId)
        .interpolatedWith (getLookAndFeel().findColour (ListBox::textColourId), 0.03f);
        g.fillAll (alternateColour);
    }
    
    void paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool rowIsSelected) override
    {
        g.setColour (getLookAndFeel().findColour (ListBox::textColourId));
        auto text = data[rowNumber].getReference(columnId - 1);
        g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
        g.setColour (getLookAndFeel().findColour (ListBox::backgroundColourId));
        g.fillRect (width - 1, 0, 1, height);
    }
    
    void addRowData(const StringArray itemsStringArray) {
        data.push_back(itemsStringArray);
    }
    
    void updateContent() {
        table.updateContent();
        table.repaint();
    }
    
    void clearItems() {
        data.clear();
    }
    
    void resized() override {
        table.setBounds(getLocalBounds());
    }
    
private:
    TableListBox table;
    std::vector<StringArray> data;
};


class FreesoundSearchComponent: public Component,
                                public Button::Listener
{
public:
    
    FreesoundSearchComponent ()
    {
        searchInput.setText("", dontSendNotification);
        searchInput.setColour (Label::backgroundColourId, getLookAndFeel().findColour (ResizableWindow::backgroundColourId).brighter());
        searchInput.setEditable (true);
        addAndMakeVisible (searchInput);
        
        searchButton.addListener (this);
        searchButton.setButtonText("Go!");
        addAndMakeVisible (searchButton);
        
        addAndMakeVisible (searchResults);
    }
    
    ~FreesoundSearchComponent ()
    {
    }
    
    void setProcessor (FreesoundSimpleSamplerAudioProcessor* p)
    {
        processor = p;
    }
    
    void paint (Graphics& g) override
    {
    }
    
    void resized () override
    {
        float unitMargin = 10;
        float searchButtonWidth = 100;
        float inputHeight = 20;
        
        searchInput.setBounds(0, 0, getWidth() - unitMargin - searchButtonWidth, inputHeight);
        searchButton.setBounds(getWidth()  - searchButtonWidth, 0, searchButtonWidth, inputHeight);
        searchResults.setBounds(0, inputHeight + unitMargin, getWidth(), getHeight() - (inputHeight + unitMargin));
    }
    
    void buttonClicked (Button* button) override
    {
        if (button == &searchButton)
        {
            Array<FSSound> sounds = searchSounds();

            processor->newSoundsReady(sounds);
        }
    }
    
    Array<FSSound> searchSounds ()
    {
        // Makes a query to Freesound to retrieve short sounds using the query text from searchInput label
        // Sorts the results randomly and chooses the first 16 to be automatically assinged to the pads
        
        String query = searchInput.getText(true);
        FreesoundClient client(FREESOUND_API_KEY);
        SoundList list = client.textSearch(query, "duration:[0 TO 0.5]", "score", 1, -1, 150, "id,name,username,license,previews");
        Array<FSSound> sounds = list.toArrayOfSounds();
        std::random_shuffle(sounds.begin(), sounds.end());
        sounds.resize(16);
        
        // Update results table
        searchResults.clearItems();
        for (int i=0; i<sounds.size(); i++){
            FSSound sound = sounds[i];
            StringArray soundData;
            soundData.add(sound.name);
            soundData.add(sound.user);
            soundData.add(sound.license);
            searchResults.addRowData(soundData);
        }
        searchResults.updateContent();
        
        return sounds;
    }
    
private:
    
    FreesoundSimpleSamplerAudioProcessor* processor;
    
    Label searchInput;
    TextButton searchButton;
    ResultsTableComponent searchResults;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreesoundSearchComponent);
};
