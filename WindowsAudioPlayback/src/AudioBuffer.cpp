#include "AudioBufferLoop.h"

AudioBufferLoop::AudioBufferLoop( )
{

}

AudioBufferLoop::~AudioBufferLoop( )
{

}

void AudioBufferLoop::Initialize( )
{
    // TODO: setup code here for the audio buffer loop, setting loop points, etc.
}
/*
void AudioBufferLoop::FillAudioBuffer( int16_t* pBuffer, size_t bufferSize )
{
    // Check if the audio data is not prepared or no more audio data is available
    if ( !audioData || audioDataPosition >= audioDataSize )
    {
        // Fill the buffer with silence
        memset( pBuffer, 0, bufferSize * sizeof( int16_t ) );
        return;
    }

    // Calculate the number of frames that can be copied into the buffer
    size_t framesToCopy = bufferSize / channels;
    size_t framesAvailable = (audioDataSize - audioDataPosition) / channels;
    framesToCopy = std::min( framesToCopy, framesAvailable );

    // Copy audio data to the buffer
    memcpy( pBuffer, &audioData[audioDataPosition], framesToCopy * channels * sizeof( int16_t ) );

    // Update the audio data position
    audioDataPosition += framesToCopy * channels;

    // If the audio data has reached its end, start the loop from the beginning
    if ( audioDataPosition >= audioDataSize )
    {
        audioDataPosition = loopStartFrame;
    }
}*/