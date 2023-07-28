#include "DeviceManager.h"
#include "Utility.h"
#include "WindowsAudioPlayer.h"

#include <iostream>
#include <vector>

#include <mmdeviceapi.h> // IMMDevice...
#include <Functiondiscoverykeys_devpkey.h>

DeviceManager::DeviceManager( )
{

}

DeviceManager::~DeviceManager( )
{

}

void DeviceManager::EnumerateAudioDevices( )
{
    Utility utility;

    HRESULT hr = CoInitializeEx( nullptr, COINIT_MULTITHREADED );
    if ( FAILED( hr ) )
    {
        utility.PrintErrorMessage( "Failed to initialize COM", hr );
        return;
    }

    IMMDeviceEnumerator* pEnumerator = nullptr;
    hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator),
        nullptr,
        CLSCTX_ALL,
        __uuidof(IMMDeviceEnumerator),
        (void**)&pEnumerator
    );
    if ( FAILED( hr ) )
    {
        utility.PrintErrorMessage( "Failed to create device enumerator", hr );
        CoUninitialize( );
        return;
    }

    IMMDeviceCollection* pDeviceCollection = nullptr;
    hr = pEnumerator->EnumAudioEndpoints( eRender, DEVICE_STATE_ACTIVE, &pDeviceCollection );
    if ( FAILED( hr ) )
    {
        utility.PrintErrorMessage( "Failed to enumerate audio endpoints", hr );
        pEnumerator->Release( );
        CoUninitialize( );
        return;
    }

    UINT deviceCount = 0;
    pDeviceCollection->GetCount( &deviceCount );

    audioDevices.clear( );

    for ( UINT i = 0; i < deviceCount; ++i )
    {
        IMMDevice* pDevice = nullptr;
        pDeviceCollection->Item( i, &pDevice );

        LPWSTR deviceId = nullptr;
        pDevice->GetId( &deviceId );

        IPropertyStore* pPropertyStore = nullptr;
        pDevice->OpenPropertyStore( STGM_READ, &pPropertyStore );

        PROPVARIANT propVariant;
        PropVariantInit( &propVariant );

        hr = pPropertyStore->GetValue( PKEY_Device_FriendlyName, &propVariant );
        if ( SUCCEEDED( hr ) && propVariant.vt == VT_LPWSTR )
        {
            AudioDeviceInfo deviceInfo;

            deviceInfo.id = utility.WideCharToString( deviceId );
            deviceInfo.name = utility.WideCharToString( propVariant.pwszVal );

            audioDevices.push_back( deviceInfo );
        }

        PropVariantClear( &propVariant );

        pPropertyStore->Release( );
        pDevice->Release( );
    }

    pDeviceCollection->Release( );
    pEnumerator->Release( );

    // Print the enumerated audio devices
    for ( size_t i = 0; i < audioDevices.size( ); ++i )
    {
        std::cout << i + 1 << ": " << audioDevices[i].name << std::endl;
    }

    CoUninitialize( );
}

void DeviceManager::SelectAudioDevice( )
{
    WindowsAudioPlayer audioPlayer;

    int deviceIndex = 0;
    while ( deviceIndex < 1 || deviceIndex >= audioDevices.size( ) )
    {
        std::cout << "\nEnter the number of the device to select for audio playback: ";
        std::string input;
        std::getline( std::cin, input );

        try
        {
            deviceIndex = std::stoi( input );
        }

        catch ( const std::exception& )
        {
            std::cout << "Invalid input. Please enter a valid device index." << std::endl;
            continue;
        }

        if ( deviceIndex < 1 || deviceIndex >= audioDevices.size( ) )
        {
            std::cout << "Invalid device index. Please select a valid device." << std::endl;
        }
    }

    const AudioDeviceInfo& selectedDevice = audioDevices[deviceIndex - 1];
    std::string selectedDeviceId = selectedDevice.id; // store ID for later use if needed
    audioPlayer.InitializeAudioSession( selectedDevice.id );

    std::cout << "\nSelected Audio Device: " << selectedDevice.name << std::endl;
}

std::string DeviceManager::GetSelectedDeviceID( ) const
{
    return selectedDeviceID;
}