#pragma once

#include <string>

#include <codecvt>
#include <locale>

#include <mmdeviceapi.h>

class Utility
{
public:

    static std::wstring StringToWSTR( const std::string& );
    static std::string WideCharToString( const wchar_t* wideString );
    HRESULT ConfigureAudioFormat( WAVEFORMATEX** ppAudioFormat );
    static void PrintErrorMessage( const std::string& errorMessage, HRESULT hr );

};