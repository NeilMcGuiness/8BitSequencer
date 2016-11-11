/*
  ==============================================================================

    Audio.cpp
    Created: 13 Nov 2014 8:14:40am
    Author:  Tom Mitchell

  ==============================================================================
*/

#include "Audio.h"

Audio::Audio()
{
    audioDeviceManager.initialiseWithDefaultDevices (2, 2); //2 inputs, 2 outputs
    
    
    audioDeviceManager.addMidiInputCallback (String::empty, this);
    audioDeviceManager.addAudioCallback (this);
}

Audio::~Audio()
{
    audioDeviceManager.removeAudioCallback (this);
    audioDeviceManager.removeMidiInputCallback (String::empty, this);
}

Looper& Audio::getLooper(int LooperNum)
{
    LooperNum > MAX_NUM_LOOPERS ? LooperNum = MAX_NUM_LOOPERS : LooperNum = LooperNum;
    
    if (LooperNum == 1)
        return looper;
    
    else if (LooperNum == 2)
        return looper2;
    
    else
        return looper;
    
    

}


void Audio::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    //All MIDI inputs arrive here
    if (message.isNoteOn())
    {
        
    }
    else if (message.isNoteOff())
    {
        
    }
}

void Audio::audioDeviceIOCallback (const float** inputChannelData,
                                           int numInputChannels,
                                           float** outputChannelData,
                                           int numOutputChannels,
                                           int numSamples)
{
    //All audio processing is done here
    const float *inL = inputChannelData[0];
    const float *inR = inputChannelData[1];
    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
    
    while(numSamples--)
    {
        float output = 0.f;
        
        output = (looper.processSample (*inL) + looper2.processSample(*inL)) * 0.707;
        
        *outL = output;
        *outR = output;
        
        inL++;
        inR++;
        outL++;
        outR++;
    }
}


void Audio::audioDeviceAboutToStart (AudioIODevice* device)
{
    
}

void Audio::audioDeviceStopped()
{

}
