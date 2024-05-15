#ifndef FFT_AUDIO_PROCESSING_CAPTURE_AUDIO_H
#define FFT_AUDIO_PROCESSING_CAPTURE_AUDIO_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

#include <portaudio.h>
#include <fftw3.h>
#define SAMPLE_RATE 44100.0
#define FRAMES_PER_BUFFER 512
#define NUM_CHANNELS 2
#define SPECTRO_FREQ_START 20
#define SPECTRO_FREQ_END 20000

typedef struct {
    double* in;
    double* out;
    fftw_plan p;
    int startIndex;
    int spectroSize;
} streamCallbackData;

static streamCallbackData* spectroData;


static int streamCallback(
        const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
        void* userData
) {
    auto* in = (float*)inputBuffer;
    (void)outputBuffer;
    auto* callbackData = (streamCallbackData*)userData;
    int dispSize = 150;
    std::cout<<"\r";
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        callbackData->in[i] = in[i * NUM_CHANNELS];
    }
    fftw_execute(callbackData->p);
    for (int i = 0; i < dispSize; i++) {
        double proportion = std::pow(i / (double)dispSize, 4);
        double freq = callbackData->out[(int)(callbackData->startIndex
                                              + proportion * callbackData->spectroSize)];
        if (freq < 0.125) {
            std::cout<<"▁";
        } else if (freq < 0.25) {
            std::cout<<"▂";
        } else if (freq < 0.375) {
            std::cout<<"▃";
        } else if (freq < 0.5) {
            std::cout<<"▄";
        } else if (freq < 0.625) {
            std::cout<<"▅";
        } else if (freq < 0.75) {
            std::cout<<"▆";
        } else if (freq < 0.875) {
            std::cout<<"▇";
        } else {
           std::cout<<"█";
        }
    }
    fflush(stdout);  //need this to maintain continuity
    return 0;
}
#endif //FFT_AUDIO_PROCESSING_CAPTURE_AUDIO_H
