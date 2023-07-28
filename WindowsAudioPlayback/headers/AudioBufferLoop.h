#pragma once
#pragma once

#include <vector>

class AudioBufferLoop
{
public:
    AudioBufferLoop( );
    ~AudioBufferLoop( );

    void Initialize( );

    // Function to fill the audio buffer with data
    void FillAudioBuffer( int16_t* pBuffer, size_t bufferSize );
};