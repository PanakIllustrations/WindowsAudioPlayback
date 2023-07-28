#pragma once

#include <string>

#include "AudioBufferLoop.h"
#include "AudioProcessor.h"

class WindowsAudioPlayer
{
public:
    WindowsAudioPlayer( );
    ~WindowsAudioPlayer( );

    void InitializeAudioSession( const std::string& );
    void PlayAudio( const std::string& );

private:
    AudioBufferLoop audioBufferLoop;
    AudioProcessor audioProcessor;
};