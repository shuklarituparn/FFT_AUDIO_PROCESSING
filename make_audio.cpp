/*
 * A simple C++ program that generated audio in the WAV format
 *
 * Every thing about the WAV format can be checked here:
 * http://soundfile.sapp.org/doc/WaveFormat/
 *
 * Channel: 2 is stereo
 *
 * SampleRate: How many sample is there per second
 *
 * BitsPerSample: 16 meaning 2 bytes of data or 16 bits
 *
 */

#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;

// MICROSOFT RIFF FORMAT HEADER
const string chunk_id = "RIFF";
const string chunk_size = "----";  // As need 4 bytes for chunk_id
const string format = "WAVE";

// FORMAT OF THE SOUND
const string subchunk1_id = "fmt ";  // Need 4 bytes here
const int subchunk1_size = 16;       // bits
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
const string subchunk2_id = "data";
const string subchunk2_size = "----";

const int duration =
        4;  // duration of the file size that we created. 2 seconds long
const int max_amplitude = 32760;  // Max amplitude, as we have 16 bytes so 2^8
// is the positive integers, -1 for the signed
const double frequency =
        350.0;  // The freq value, the higher it is the closer the wave is

void write_as_bytes(ofstream& file, int value, int byte_size) {
    file.write(
            reinterpret_cast<const char*>(&value),
            byte_size);  // To convert the int to char, and sending it as char pointer
}

int main() {
    ofstream wav;
    wav.open("test.wav", ios::binary);  // making the file as binary
    if (wav.is_open()) {
        // Writing the RIFF format
        wav << chunk_id;
        wav << chunk_size;
        wav << format;

        // Write the format
        wav << subchunk1_id;
        write_as_bytes(wav, subchunk1_size, 4);
        write_as_bytes(wav, audio_format, 2);
        write_as_bytes(wav, num_channels, 2);
        write_as_bytes(wav, sample_rate, 4);
        write_as_bytes(wav, byte_rate, 4);
        write_as_bytes(wav, block_align, 2);
        write_as_bytes(wav, bits_per_sample, 2);

        // We write the data
        wav << subchunk2_id;
        wav << subchunk2_size;

        int start_audio = wav.tellp();
        for (int i = 0; i < sample_rate * duration;
             ++i) {  // It needs to go to the sample rate and the duration
            double amplitude =
                    (double)i / sample_rate *
                    max_amplitude;  // We make the amplitude vary but stays in the max, so
            // the sound amplitude highs
            double value = sin((2 * M_PI * i * frequency) / sample_rate);

            double channel1 = amplitude * value / 2;
            double channel2 = (max_amplitude - amplitude) * value;

            write_as_bytes(wav, channel1, 2);
            write_as_bytes(wav, channel2, 2);
        }
        int end_audio = wav.tellp();
        wav.seekp(start_audio - 4);
        write_as_bytes(wav, end_audio - start_audio, 4);
        wav.seekp(4, ios::beg);
        write_as_bytes(wav, end_audio - 8, 4);
    }
    wav.close();

    return 0;
}
