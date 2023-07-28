#pragma once

#include <vector>
#include <cstdint>
#include <string>

class AudioProcessor
{
public:
    AudioProcessor( );
    ~AudioProcessor( );

    void Initialize( const std::string deviceID );
    // Add a new channel with a given waveform data
    void AddChannel( const std::vector<uint8_t>& waveformData, double frequency, double volume );

    // Clear all channels
    void ClearChannels( );

    // Generate audio samples for a given number of frames
    // Returns true if more data is available, false if not
    bool GenerateAudioSamples( uint32_t numFrames, std::vector<int16_t>& outputBuffer );

private:
    struct Channel
    {
        std::vector<uint8_t> waveformData;
        double frequency;
        double volume;
        uint32_t position;
    };

    std::vector<Channel> channels;
};
