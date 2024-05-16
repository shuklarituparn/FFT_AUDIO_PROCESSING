#include "../include/capture_audio.h"

int main() {
    Pa_Initialize();
    // allocating the data to the heap
    spectroData = (streamCallbackData*)malloc(sizeof(streamCallbackData));
    // input buffer 512 element long, to use in fftw
    spectroData->in = new double[FRAMES_PER_BUFFER];
    // same as output
    spectroData->out = new double[FRAMES_PER_BUFFER];
    if (spectroData->in == nullptr || spectroData->out == nullptr) {
        std::cout << "Error creating an array of input/output buffers: ";
        return 1;
    }
    // p is the plan that we declared the plan, here we use real to real fft
    spectroData->p = fftw_plan_r2r_1d(
            // n is how big the data is, in the where to find the data, out is where
            // to write data to
            FRAMES_PER_BUFFER, spectroData->in, spectroData->out,
            // kind is Real To Half Complex, first n/2 is real and second n/2 is the
            // complex number
            FFTW_R2HC, FFTW_ESTIMATE
            // flag to pick a (probably sub-optimal) plan quickly. With this flag, the
            // input/output arrays are not overwritten during planning.
    );
    // to calculate the freq
    double sampleRatio = FRAMES_PER_BUFFER / SAMPLE_RATE;
    // the index of the freq start 20hz
    spectroData->startIndex = std::ceil(sampleRatio * SPECTRO_FREQ_START);
    // to get the last frew
    spectroData->spectroSize =
            std::min(
                    // index of the last freq
                    std::ceil(sampleRatio * SPECTRO_FREQ_END), FRAMES_PER_BUFFER / 2.0) -
            spectroData->startIndex;
    int numDevices = Pa_GetDeviceCount();

    if (numDevices < 0) {
        std::cout << "Error getting device count.\n";
        return 1;
    } else if (numDevices == 0) {
        std::cout << "There are no available audio devices on this machine.\n";
        return 1;
    }
    int device = 1;
    PaStreamParameters inputParameters;
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.device = device;
    inputParameters.hostApiSpecificStreamInfo = nullptr;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency =
            Pa_GetDeviceInfo(device)->defaultLowInputLatency;
    PaStream* stream;
    Pa_OpenStream(&stream, &inputParameters, nullptr, SAMPLE_RATE,
                  FRAMES_PER_BUFFER, paNoFlag, streamCallback,
                  spectroData  // userdata
    );
    Pa_StartStream(stream);
    Pa_Sleep(60 * 1000);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    fftw_destroy_plan(spectroData->p);
    fftw_free(spectroData->in);
    fftw_free(spectroData->out);
    free(spectroData);
    return 0;
}