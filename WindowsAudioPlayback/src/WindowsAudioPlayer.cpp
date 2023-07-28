#include "WindowsAudioPlayer.h"
#include "utility.h"
#include "DeviceManager.h"
#include "AudioBufferLoop.h"
#include "AudioProcessor.h"

#include <iostream>
#include <string>

#include <Windows.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <Functiondiscoverykeys_devpkey.h>

WindowsAudioPlayer::WindowsAudioPlayer( )
{

}

WindowsAudioPlayer::~WindowsAudioPlayer( )
{

}

void WindowsAudioPlayer::InitializeAudioSession( const std::string& deviceID_Str )
{
    Utility utility;
    HRESULT hr = CoInitializeEx( nullptr, COINIT_MULTITHREADED );

    // Create an instance of the MMDeviceEnumerator
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
        return;
    }
    std::wstring temp = (utility.StringToWSTR( deviceID_Str ));
    LPCWSTR deviceID = temp.c_str( );

    // Get the selected audio device based on the device ID
    IMMDevice* pDevice = nullptr;
    hr = pEnumerator->GetDevice( deviceID, &pDevice );
    if ( FAILED( hr ) )
    {
        if ( hr == E_NOTFOUND )
        {
            std::cout << "Audio device not found" << std::endl;
        }
        else
        {
            utility.PrintErrorMessage( "Failed to get selected audio device", hr );
        }

        pEnumerator->Release( );
        return;
    }

    // Activate the audio client interface
    IAudioClient* pAudioClient = nullptr;
    hr = pDevice->Activate( __uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&pAudioClient );
    if ( FAILED( hr ) )
    {
        utility.PrintErrorMessage( "Failed to activate audio client", hr );
        pDevice->Release( );
        pEnumerator->Release( );
        return;
    }

    // Configure the audio format and initialize the audio client
    WAVEFORMATEX* pAudioFormat = nullptr;
    hr = utility.ConfigureAudioFormat( &pAudioFormat );
    if ( FAILED( hr ) )
    {
        utility.PrintErrorMessage( "Failed to configure audio format", hr );
        pAudioClient->Release( );
        pDevice->Release( );
        pEnumerator->Release( );
        return;
    }

    // Check if the audio format is supported by the audio client
    hr = pAudioClient->IsFormatSupported( AUDCLNT_SHAREMODE_SHARED, pAudioFormat, &pAudioFormat );
    if ( FAILED( hr ) )
    {
        if ( hr == AUDCLNT_E_UNSUPPORTED_FORMAT )
        {
            std::cout << "Unsupported audio format" << std::endl;
        }
        else
        {
            utility.PrintErrorMessage( "Failed to check audio format support", hr );
        }

        CoTaskMemFree( pAudioFormat );
        pAudioClient->Release( );
        pDevice->Release( );
        pEnumerator->Release( );
        return;
    }

    // Initialize the audio client
    hr = pAudioClient->Initialize( AUDCLNT_SHAREMODE_SHARED, 0, 0, 0, pAudioFormat, 0 );
    if ( FAILED( hr ) )
    {
        utility.PrintErrorMessage( "Failed to initialize audio client", hr );

        CoTaskMemFree( pAudioFormat );
        pAudioClient->Release( );
        pDevice->Release( );
        pEnumerator->Release( );
        return;
    }

    IAudioRenderClient* pRenderClient = nullptr;
    hr = pAudioClient->GetService( __uuidof(IAudioRenderClient), (void**)&pRenderClient );
    if ( FAILED( hr ) )
    {
        utility.PrintErrorMessage( "Failed to get IAudioRenderClient interface", hr );
        return;
    }

    // Cleanup and release resources
    CoTaskMemFree( pAudioFormat );
    pAudioClient->Release( );
    pDevice->Release( );
    pEnumerator->Release( );

    // Audio session initialization successful
    std::cout << "Audio session initialized successfully" << std::endl;
}

void WindowsAudioPlayer::PlayAudio( const std::string& selectedDeviceID )
{
    AudioProcessor audioProcessor;
    AudioBufferLoop audioBufferLoop;

    audioProcessor.Initialize( selectedDeviceID );
    audioBufferLoop.Initialize( );

}

/*void WindowsAudioPlayer::ConfigureAudioFormat( )
{
    // Audio format configuration implementation
}*/
