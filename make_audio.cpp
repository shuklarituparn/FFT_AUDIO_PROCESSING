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

#include "make_audio.h"

int main() {
    std::cout<<"Enter the duration of the audio wave you want to create in seconds";
    std::cin>>duration;
    std::cout<<"Enter the frequency of the audio wave you want to make: ";
    std::cin>>frequency;
    std::ofstream wav;
    wav.open("test.wav", std::ios::binary);  // making the file as binary
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

        int start_audio = wav.tellp();  //start of audio
        for (int i = 0; i < sample_rate * duration;
             ++i) {  // It needs to go to the sample rate and the duration
            double amplitude =
                    (double)i / sample_rate *
                    max_amplitude;  // We make the amplitude vary but stays in the max, so
            // the sound amplitude highs
            double value = sin((2 * M_PI * i * frequency) / sample_rate);

            double channel1 = amplitude * value / 2;
            double channel2 = (max_amplitude - amplitude) * value;

            write_as_bytes(wav, channel1, 2);  //the effect
            write_as_bytes(wav, channel2, 2);
        } //end of audio
        //after this loop we still don't have the data, we need to populate the chunk
        int end_audio = wav.tellp();
        wav.seekp(start_audio - 4); //going to the just before the start_audio to write the audio data
        //since the start_audio is 4 bytes we deduct that much
        write_as_bytes(wav, end_audio - start_audio, 4); //writing the data
        wav.seekp(4, std::ios::beg); //going to the beginning, and then 4 bytes after it to write the chunk size
        write_as_bytes(wav, end_audio - 8, 4);
    }
    wav.close();
    return 0;
}
