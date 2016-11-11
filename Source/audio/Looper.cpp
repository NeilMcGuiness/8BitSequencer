//
//  Looper.cpp
//  sdaLooper
//
//  Created by tj3-mitchell on 21/01/2013.
//
//

#include "Looper.h"

Looper::Looper()
{
    //initialise - not playing / recording
    playState = false;
    recordState = false;
    //position to the start of audioSampleBuffer
    bufferPosition = 0;
    
    //audioSampleBuffer contents to zero
    for (int count = 0; count < bufferSize; count++)
        audioSampleBuffer[count] = 0.f;

}

Looper::~Looper()
{

}

void Looper::setPlayState (const bool newState)
{
    playState = newState;
}

bool Looper::getPlayState () const
{
    return playState.get();
}

void Looper::setRecordState (const bool newState)
{
    recordState = newState;
}

bool Looper::getRecordState () const
{
    return recordState.get();
}

float Looper::processSample (float input)
{
    float output = 0.f;
    if (playState.get() == true)
    {
        //play
        output = audioSampleBuffer[bufferPosition];
        //click 4 times each bufferLength
        if ((bufferPosition % (bufferSize / 4)) == 0)
            output += 0.25f;
        
        //record
        if (recordState.get() == true)
            audioSampleBuffer[bufferPosition] += input;
        
        //increment and cycle the buffer counter
        ++bufferPosition;
        if (bufferPosition == bufferSize)
            bufferPosition = 0;
    }
    return output;
}
