#pragma once
#include <fftw3.h>
#include <portaudio.h>

#include <cmath>
#include <iostream>
#define SAMPLE_RATE \
  44100.0  // computer extracting the sound level at 1 point at that interval in
// time so 44k times/second
#define FRAMES_PER_BUFFER 512  // storing the 512 of the value
#define NUM_CHANNELS 2
#define SPECTRO_FREQ_START 20   // lower bound that our program is sensible to
#define SPECTRO_FREQ_END 20000  // upper bound our program is sensible to

struct streamCallbackData {
    double* in;       // storing the input buffer
    double* out;      // output the buffer
    fftw_plan p;      // the plan that fftw library needs to execute
    int startIndex;   // the start index in the freq
    int spectroSize;  // freq index
};

static streamCallbackData* spectroData;

static int streamCallback(  // the 512 value goes here
        const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
        void* userData  // user data that user modifies
) {
    auto* in = (float*)inputBuffer;
    (void)outputBuffer;
    auto* callbackData = (streamCallbackData*)
            userData;  // casting the userdata to the streamcallback data
    // because userdata is pointing to
    int dispSize = 150;
    std::cout << "\r";
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        callbackData->in[i] =
                in[i * NUM_CHANNELS];  // audio input buffer and its channel, audio
        // sample from first channel
    }
    fftw_execute(callbackData->p);
    // Now output data will have all the freq data
    for (int i = 0; i < dispSize; i++) {
        double proportion = std::pow(i / (double)dispSize, 4);
        double freq =
                callbackData->out[(int)(callbackData->startIndex +
                                        proportion * callbackData->spectroSize)];
        if (freq < 0.125) {
            std::cout << "▁";
        } else if (freq < 0.25) {
            std::cout << "▂";
        } else if (freq < 0.375) {
            std::cout << "▃";
        } else if (freq < 0.5) {
            std::cout << "▄";
        } else if (freq < 0.625) {
            std::cout << "▅";
        } else if (freq < 0.75) {
            std::cout << "▆";
        } else if (freq < 0.875) {
            std::cout << "▇";
        } else {
            std::cout << "█";
        }
    }
    fflush(stdout);  // need this to maintain continuity
    return 0;
}
