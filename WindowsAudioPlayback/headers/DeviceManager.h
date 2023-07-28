#pragma once

#include <string>
#include <vector>

struct AudioDeviceInfo
{
    std::string id;
    std::string name;

};

class DeviceManager
{
public:
    DeviceManager( );
    ~DeviceManager( );

    void EnumerateAudioDevices( );
    void SelectAudioDevice( );

    std::string GetSelectedDeviceID( ) const;

private:
    AudioDeviceInfo deviceInfo;
    std::vector<AudioDeviceInfo> audioDevices;
    std::string selectedDeviceID;
};