/*
  ==============================================================================

    Audio.h
    Created: 13 Nov 2014 8:14:40am
    Author:  Tom Mitchell

  ==============================================================================
*/

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

/**
 Class containing all audio processes
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "Looper.h"
#define MAX_NUM_LOOPERS 2
class Audio :   public MidiInputCallback,
                public AudioIODeviceCallback
{
public:
    /** Constructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** Returns the audio device manager, don't keep a copy of it! */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager; }
    
    Looper& getLooper(int LooperNum); 
    
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
    
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    
    void audioDeviceStopped() override;
private:
    AudioDeviceManager audioDeviceManager;
    Looper looper;
    Looper looper2;
};



#endif  // AUDIO_H_INCLUDED
