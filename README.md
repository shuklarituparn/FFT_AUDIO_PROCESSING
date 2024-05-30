
# FFT AUDIO_PROCESSING

<p align="center">
  <img src="docs/fftw-logo-med.gif" width="400" height="200">
  <img src="docs/ISO_C++_Logo.svg.png" width="200" height="200">
</p>

Creating and Processing Audio using FFT
## Run Locally

Clone the project

```bash
 git clone git@github.com:shuklarituparn/FFT_AUDIO_PROCESSING.git
```

Go to the project directory

```bash
   cd FFT_AUDIO_PROCESSING

```

---

### Makefile

- To install the required dependencies run the following commands while in the root directory

 ```bash
 
   make install_fftw
 
 ```

- To compile the audio generation program, type the following command in the terminal

```bash
    make cppaudiogenerate
```

- To run the audio generation program, type the following command in the terminal

```bash
    .bin/cppaudiogenerate
```
The program will ask you the frequency of the audio file to generate and the length and will generate a ```.WAVE``` audio file

- To compile the audio capture program, type the following command in the terminal

```bash
    make cppaudiocapture
```

- To run the audio capture program, type the following command in the terminal

```bash
    ./cppaudiocapture
```


You will see an audio analyzer on the terminal, by default it will run for 30 seconds

- To clean the executables after running the program, run the following command

```bash
  make clean
```
