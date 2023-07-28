# (WIP) Audio Processing Program

## Overview

The audio processing program is designed to provide a flexible and dynamic platform for generating and manipulating audio waveforms. It allows users to create custom waveforms, apply various effects, and play the audio through selected output devices.

## Features

- Waveform Generation: Users can create custom waveforms using mathematical formulas, allowing for precise control over the audio output.
- Effect Application: The program supports various audio effects, such as reverb, fade-in, and fade-out, which can be applied to the generated waveforms.
- Multiple Channels: The application supports up to 5 channels, replicating the characteristics of the NES audio system, including two pulse wave channels, one triangle wave channel, one white noise channel, and one sample channel.
- User Input: Users can interactively define the parameters for waveform generation and effect application, providing real-time feedback and customization options.
- Multi-Threading: The program uses multi-threading to efficiently handle audio processing and playback, ensuring smooth and uninterrupted audio output.

## Getting Started

To run the audio processing program, follow these steps:

1. Compile and build the program using a C++ compiler.
2. Launch the executable file to open the audio processing application.

## Usage

1. Audio Device Selection: The program will prompt the user to select an audio output device from the available list of devices.
2. Waveform Generation: Users can specify the parameters of the waveform they wish to generate, including frequency, amplitude, and waveform type (e.g., sine, square, triangle).
3. Effect Application: Users can apply various audio effects to the generated waveform, such as reverb, fade-in, and fade-out, using the provided controls.
4. Playback: Once the audio is generated and effects are applied, users can play the audio to the selected output device for real-time listening.
5. Multi-Channel Output: The program will mix and output the audio to the specified channels, replicating the NES audio system's behavior.

## Error Handling

The program includes comprehensive error handling mechanisms to handle potential issues during audio device initialization, waveform generation, and effect application. Error messages and relevant information will be displayed to the user to help diagnose and address any problems that may arise.

## Known Issues

At present, the program is in an unfinished state, and certain features, such as the initialization functions and the missing `GetSelectedDeviceID` method, are yet to be defined. Additionally, the interaction between `AudioProcessor` and `AudioBufferLoop` in the context of `WindowsAudioPlayer` requires further refinement.

## Feedback and Contributions

This audio processing program is an ongoing project for educational purposes and feedback is encouraged. If you have any suggestions, ideas, or improvements, please feel free to provide your feedback.
