#include "AudioProcessor.h"
#include <cmath>
#include <string>

constexpr double PI = 3.141592653589793238463;

AudioProcessor::AudioProcessor( )
{
}

AudioProcessor::~AudioProcessor( )
{
}

void AudioProcessor::Initialize( const std::string deviceID )
{
    // TODO: setup initializing audio processing, effects, etc.
}

void AudioProcessor::AddChannel( const std::vector<uint8_t>& waveformData, double frequency, double volume )
{
    Channel channel;
    channel.waveformData = waveformData;
    channel.frequency = frequency;
    channel.volume = volume;
    channel.position = 0;
    channels.push_back( channel );
}

void AudioProcessor::ClearChannels( )
{
    channels.clear( );
}

bool AudioProcessor::GenerateAudioSamples( uint32_t numFrames, std::vector<int16_t>& outputBuffer )
{
    outputBuffer.resize( numFrames, 0 );

    for ( uint32_t frame = 0; frame < numFrames; ++frame )
    {
        int32_t mixedSample = 0;

        for ( auto& channel : channels )
        {
            if ( channel.position < channel.waveformData.size( ) )
            {
                double angle = (2.0 * PI * channel.position * channel.frequency) / 44100.0;
                int16_t sampleValue = static_cast<int16_t>(std::round( channel.volume * 127.0 * std::sin( angle ) ));
                mixedSample += sampleValue;
                channel.position++;
            }
        }

        mixedSample = std::max( std::min( mixedSample, 32767 ), -32768 );
        outputBuffer[frame] = static_cast<int16_t>(mixedSample);
    }

    return true;
}
