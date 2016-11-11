//
//  LooperGui.h
//  sdaLooper
//
//  Created by tj3-mitchell on 21/01/2013.
//
//

#ifndef H_LooperGui
#define H_LooperGui

#include "../JuceLibraryCode/JuceHeader.h"
#include "Looper.h"

/**
 Gui for the looper class
 */
class LooperGui :   public Component,
                    public Button::Listener
{
public:
    /**
     constructor - receives a reference to a Looper object to control
     */
    LooperGui(Looper& looper_);
    
    //Button Listener
    void buttonClicked (Button* button);
    
    //Component
    void resized();
private:
    Looper& looper;                 //reference to a looper object
    TextButton playButton;
    TextButton recordButton;
    TextButton saveButton;
    TextButton loadButton;
};

#endif
