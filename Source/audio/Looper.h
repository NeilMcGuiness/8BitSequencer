//
//  Looper.h
//  sdaLooper
//
//  Created by tj3-mitchell on 21/01/2013.
//
//

#ifndef H_Looper
#define H_Looper

#include "../JuceLibraryCode/JuceHeader.h"

/**
 Simple audio looper class - loops an audio buffer and records its input into the buffer.
 Also produces a click 4 times each loop.
 */
class Looper
{
public:
    /**
     Constructor - initialise everything 
     */
    Looper();
    
    /**
     Destructor
     */
    ~Looper();
    
    /**
     Starts or stops playback of the looper
     */
    void setPlayState (bool newState);
    
    /**
     Gets the current playback state of the looper
     */
    bool getPlayState() const;
    
    /**
     Sets/unsets the record state of the looper
     */
    void setRecordState (bool newState);
    
    /**
     Gets the current record state of the looper
     */
    bool getRecordState() const;
    
    /**
     Processes the audio sample by sample.
     */
    float processSample (float input);

private:  
    //Shared data
    Atomic<int> recordState;
    Atomic<int> playState;
    
    //Audio data
    static const int bufferSize = 88200; //constant
    unsigned int bufferPosition;
    float audioSampleBuffer[bufferSize];
};

#endif /* H_Looper */