/*
  ==============================================================================

    FreesoundSearchComponent.h
    Created: 10 Sep 2019 5:44:51pm
    Author:  Frederic Font Corbera

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FreesoundAPI.h"
#include "api_key.h"


class FreesoundSearchComponent: public Component,
                                public Button::Listener
{
public:
    
    FreesoundSearchComponent ()
    {
        searchInput.setText("type your query here", dontSendNotification);
        searchInput.setEditable (true);
        addAndMakeVisible (searchInput);
        
        searchButton.addListener (this);
        searchButton.setButtonText("Go!");
        addAndMakeVisible (searchButton);
    }
    
    ~FreesoundSearchComponent ()
    {
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
    }
    
    void buttonClicked (Button* button) override
    {
        if (button == &searchButton)
        {
            // TODO
        }
    }
    
private:
    
    Label searchInput;
    TextButton searchButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreesoundSearchComponent);
};
