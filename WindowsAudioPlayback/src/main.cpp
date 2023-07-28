#include "WindowsAudioPlayer.h"
#include "DeviceManager.h"


#include <iostream>

#include <Windows.h>

int main( )
{
    // Initialize the device manager and enumerate audio devices
    DeviceManager deviceManager;
    deviceManager.EnumerateAudioDevices( );

    // Let the user select an audio device
    deviceManager.SelectAudioDevice( );

    // Get the selected device ID
    std::string deviceID_Str = deviceManager.GetSelectedDeviceID( );

    // Initialize the audio processor with the selected device ID
    AudioProcessor audioProcessor;
    audioProcessor.Initialize( deviceID_Str );

    // Initialize the audio buffer loop
    AudioBufferLoop audioBufferLoop;
    audioBufferLoop.Initialize( );

    // Play audio using the initialized components
    WindowsAudioPlayer audioPlayer;
    audioPlayer.PlayAudio( deviceID_Str );
    return 0;
}