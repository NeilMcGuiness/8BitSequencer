//
//  LooperGui.cpp
//  sdaLooper
//
//  Created by tj3-mitchell on 21/01/2013.
//
//

#include "LooperGui.h"

LooperGui::LooperGui(Looper& looper_) : looper (looper_)
{
    playButton.setButtonText ("Play");
    playButton.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    playButton.setColour(TextButton::buttonColourId, Colours::grey);
    playButton.setColour(TextButton::buttonOnColourId, Colours::lightgrey);
    addAndMakeVisible (&playButton);
    playButton.addListener (this);
    
    recordButton.setButtonText ("Record");
    recordButton.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    recordButton.setColour(TextButton::buttonColourId, Colours::darkred);
    recordButton.setColour(TextButton::buttonOnColourId, Colours::red);
    addAndMakeVisible (&recordButton);
    recordButton.addListener (this);
    
    saveButton.setButtonText ("Save");
    saveButton.setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    saveButton.setColour(TextButton::buttonColourId, Colours::darkred);
    saveButton.setColour(TextButton::buttonOnColourId, Colours::red);
    addAndMakeVisible (&saveButton);
    saveButton.addListener (this);
}

void LooperGui::buttonClicked (Button* button)
{
    if (button == &playButton)
    {
        looper.setPlayState (!looper.getPlayState());
        playButton.setToggleState (looper.getPlayState(), dontSendNotification);
        if (looper.getPlayState())
            playButton.setButtonText ("Stop");
        else
            playButton.setButtonText ("Play");
    }
    else if (button == &recordButton)
    {
        looper.setRecordState (!looper.getRecordState());
        recordButton.setToggleState (looper.getRecordState(), dontSendNotification);

    }
    else if (button == &saveButton)
    {
        looper.load();
    }
}

void LooperGui::resized()
{
    playButton.setBounds (0, 0, getWidth()/2, getHeight()/2);
    recordButton.setBounds (playButton.getBounds().translated(getWidth()/2, 0));
    saveButton.setBounds(playButton.getBounds().translated(0, getHeight()/2));
}