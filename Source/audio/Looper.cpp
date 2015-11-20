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
    
    audioSampleBuffer.setSize (1, bufferSize);
    audioSampleBuffer.clear();
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
        //output = audioSampleBuffer[bufferPosition];
        output = *(audioSampleBuffer.getWritePointer (0, bufferPosition));
        //click 4 times each bufferLength
        if ((bufferPosition % (bufferSize / 4)) == 0)
            output += 0.25f;
        
        //record
        if (recordState.get() == true)
            *(audioSampleBuffer.getWritePointer (0, bufferPosition)) = input;
        
        //increment and cycle the buffer counter
        ++bufferPosition;
        if (bufferPosition == bufferSize)
            bufferPosition = 0;
    }
    return output;
}

void Looper::save()
{
    FileChooser chooser ("Please select a file...", File::getSpecialLocation (File::userDesktopDirectory), "*.wav");
    if (chooser.browseForFileToSave(true))
    {
        File file (chooser.getResult().withFileExtension (".wav"));
        OutputStream* outStream = file.createOutputStream();
        WavAudioFormat wavFormat;
        AudioFormatWriter* writer = wavFormat.createWriterFor (outStream, 44100, 1, 16, NULL, 0);
        writer->writeFromAudioSampleBuffer (audioSampleBuffer, 0, audioSampleBuffer.getNumSamples());
        delete writer;
    }
}


void Looper::load()
{
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    FileChooser chooser ("Please select the file you want to load...",
                         File::getSpecialLocation (File::userHomeDirectory),
                         formatManager.getWildcardForAllFormats());
    
    if (chooser.browseForFileToOpen())
    {
        File file (chooser.getResult());
        
        AudioFormatReader* reader = formatManager.createReaderFor (file);
        
        if (reader != 0)
        {
            audioSampleBuffer.setSize (reader->numChannels, reader->lengthInSamples);
            reader->read (&audioSampleBuffer, 0, reader->lengthInSamples, 0, true, false);
            delete reader;
        }
    }
}
















