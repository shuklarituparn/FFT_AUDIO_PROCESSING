#include "capture_audio.h"

int main() {
    Pa_Initialize();
    spectroData = (streamCallbackData*)malloc(sizeof(streamCallbackData));
    spectroData->in = (double*)malloc(sizeof(double) * FRAMES_PER_BUFFER);
    spectroData->out = (double*)malloc(sizeof(double) * FRAMES_PER_BUFFER);
    if (spectroData->in == nullptr || spectroData->out == nullptr) {
        std::cout<<"Could not allocate data\n";
        return 1;
    }
    spectroData->p = fftw_plan_r2r_1d(
            FRAMES_PER_BUFFER, spectroData->in, spectroData->out,
            FFTW_R2HC, FFTW_ESTIMATE
    );
    double sampleRatio = FRAMES_PER_BUFFER / SAMPLE_RATE;
    spectroData->startIndex = std::ceil(sampleRatio * SPECTRO_FREQ_START);
    spectroData->spectroSize = std::min(
            std::ceil(sampleRatio * SPECTRO_FREQ_END),
            FRAMES_PER_BUFFER / 2.0
    ) - spectroData->startIndex;
    int numDevices = Pa_GetDeviceCount();

    if (numDevices < 0) {
        std::cout<<"Error getting device count.\n";
        return 1;
    } else if (numDevices == 0) {
        std::cout<<"There are no available audio devices on this machine.\n";
        return 1;
    }
    int device = 1;
    PaStreamParameters inputParameters;
    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.device = device;
    inputParameters.hostApiSpecificStreamInfo = nullptr;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowInputLatency;
    PaStream* stream;
    Pa_OpenStream(
            &stream,
            &inputParameters,
            nullptr,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paNoFlag,
            streamCallback,
            spectroData
    );
    Pa_StartStream(stream);
    Pa_Sleep(30 * 1000);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    fftw_destroy_plan(spectroData->p);
    fftw_free(spectroData->in);
    fftw_free(spectroData->out);
    free(spectroData);
    return 0;
}