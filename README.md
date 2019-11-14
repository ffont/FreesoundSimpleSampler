[![License: AGPL v3](https://img.shields.io/badge/License-AGPL%20v3-ff69b4.svg)](http://www.gnu.org/licenses/agpl-3.0)

# FreesoundSimpleSampler
A simple JUCE sampler plugin which demonstrates the use of the freesound-juce API client. The user can create a textual query to Freesound.org and 16 random sounds are loaded in a sampler.

Usage
-------

To use this application, the user should execute it either as a standalone application or as a plugin in a Digital Audio Workstation. Then, the following steps should be performed:
* Enter a search query in the text box.
* Press the "Go!" button.
* The sounds can be triggered by pressing the sound in the list or by sending the corresponding MIDI note. The sounds use the full range of MIDI notes, with the first sounds in C0, and subsequent sounds 8 semitones apart (C0, G#0, E1, C2, G#2, E3, C4, G#4, E5, etc.). 

The user interface of this application is shown below for easy referencing.


Installation
-------

In order to install Freesound Uploader, the JUCE framework should be downloaded, installed and setup. A tutorial on how to do this is available in https://docs.juce.com/master/tutorial_new_projucer_project.html
Firstly, the "Getting Started" section should be performed. Then, the FreesoundSimpleSampler.juce file should be opened with the projucer.
Before building it you should duplicate the file `FreesoundSimpleSampler/Source/api_key.example.h`, request a Freesound API key and add it to that file, and rename it to `FreesoundSimpleSampler/Source/api_key.h`.
The final step is setting up the desired plugin export formats in the Projucer project settings and, finally you should open this project on the desired Juce exporter and build the solution.
In case a VST2 build of the plugin is desired, a VST2 SDK should be provided and linked in the Projucer global paths.

Authors
-------
António Ramires
antonio.ramires@upf.edu

Frederic Font
frederic.font@upf.edu
