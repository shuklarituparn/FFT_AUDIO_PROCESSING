EXEC = cppaudiocapture
GEN=cppaudiogenerate

CLIB = -I./lib/portaudio/include ./lib/portaudio/lib/.libs/libportaudio.a \
	-lrt -lasound  -pthread -I./lib/fftw-3.3.10/api -lfftw3

$(EXEC): monitor_audio.cpp
	g++ -o $@ $^ $(CLIB)

$(GEN): make_audio.cpp
	g++ -o $@ $^

clean:
	rm -f $(EXEC)
	rm -f $(GEN)
.PHONY: clean
