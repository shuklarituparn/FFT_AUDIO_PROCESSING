//
// Created by rituparn on 15.05.24.
//

#ifndef FFT_AUDIO_PROCESSING_MAKE_AUDIO_H
#define FFT_AUDIO_PROCESSING_MAKE_AUDIO_H

#include <cmath>
#include <fstream>
#include <iostream>

// MICROSOFT RIFF FORMAT HEADER
const std::string chunk_id = "RIFF";
const std::string chunk_size = "----";  // As need 4 bytes for chunk_id
const std::string format = "WAVE";

// FORMAT OF THE SOUND
const std::string subchunk1_id = "fmt ";  // Need 4 bytes here
const int subchunk1_size = 16;            // bits
const int audio_format =
        1;  // for PCM (https://en.wikipedia.org/wiki/Pulse-code_modulation)
const int num_channels = 2;
const int sample_rate = 44100;  // Standard samplerate 44khz
const int byte_rate = sample_rate * num_channels * (subchunk1_size / 8);
const int block_align =
        num_channels * (subchunk1_size /
                        8);  // number of bytes for 1 sample including all channels
const int bits_per_sample = 16;  // for pcm

// DATA
const std::string subchunk2_id = "data";
const std::string subchunk2_size = "----";

int duration;                     // I want to ask user for the audio
const int max_amplitude = 32760;  // Max amplitude, as we have 16 bytes so 2^8
// is the positive integers, -1 for the signed
double frequency;  // The freq value, the higher it is the closer the wave is

void write_as_bytes(std::ofstream& file, int value, int byte_size) {
    file.write(
            reinterpret_cast<const char*>(&value),
            byte_size);  // To convert the int to char, and sending it as char pointer
}

#endif  // FFT_AUDIO_PROCESSING_MAKE_AUDIO_H
