#include "WindowsAudioPlayer.h"
#include "utility.h"
#include "DeviceManager.h"

#include <iostream>
#include <string>

#include <Windows.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>

std::string Utility::WideCharToString( const wchar_t* wideString )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes( wideString );
}

std::wstring Utility::StringToWSTR( const std::string& str )
{
    std::wstring wstr( str.begin( ), str.end( ) );
    return wstr;
}

HRESULT Utility::ConfigureAudioFormat( WAVEFORMATEX** ppAudioFormat )
{
    *ppAudioFormat = static_cast<WAVEFORMATEX*>(CoTaskMemAlloc( sizeof( WAVEFORMATEX ) ));

    if ( *ppAudioFormat == nullptr )
    {
        // Failed to allocate memory for audio format
        return E_OUTOFMEMORY;
    }

    // Configure format here:
    WAVEFORMATEX* format = *ppAudioFormat;
    format->wFormatTag = WAVE_FORMAT_PCM;
    format->nChannels = 1;
    format->nSamplesPerSec = 44100;
    format->wBitsPerSample = 8;
    format->cbSize = 0;

    // Calculate nBlockAlign and nAvgBytesPerSec
    format->nBlockAlign = format->nChannels * (format->wBitsPerSample / 8);
    format->nAvgBytesPerSec = format->nSamplesPerSec * format->nBlockAlign;

    // Return success
    return S_OK;
}

void Utility::PrintErrorMessage( const std::string& errorMessage, HRESULT hr )
{
    DWORD errorCode = static_cast<DWORD>(hr);

    LPSTR systemErrorMessage = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorCode,
        MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
        reinterpret_cast<LPSTR>(&systemErrorMessage),
        0,
        nullptr
    );

    std::cout << errorMessage << std::endl;

    if ( systemErrorMessage != nullptr )
    {
        std::cout << systemErrorMessage << std::endl;
        LocalFree( systemErrorMessage );
    }
    else
    {
        std::cout << "HRESULT value: 0x" << std::hex << errorCode << std::endl;
    }
}