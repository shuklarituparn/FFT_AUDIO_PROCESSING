
# FFT AUDIO_PROCESSING



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

- To run the audio generation program, type the following command in the terminal

```bash
    make cppaudiogenerate
    ./cppaudiogenerate
```
The program will ask you the frequency of the audio file to generate and the length

- To run the audio capture program, type the following command in the terminal

```bash
    make cppaudiocapture
    ./cppaudiocapture
```

You will see an audio analyzer on the terminal, by default it will run for 30 seconds

- To clean the executables after running the program, run the following command

```bash
  make clean
```
