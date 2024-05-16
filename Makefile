EXEC = cppaudiocapture
GEN = cppaudiogenerate
CLIB = -I./lib/portaudio/include ./lib/portaudio/lib/.libs/libportaudio.a -lrt -lasound -pthread -I./lib/fftw-3.3.10/api -lfftw3
OUTPUT_DIR=./bin
.PHONY: all install_deps install_fftw clean

all: $(EXEC) $(GEN)

$(EXEC): src/monitor_audio.cpp
	g++ -o $(OUTPUT_DIR)/$@ $^ $(CLIB)

$(GEN): src/make_audio.cpp
	g++ -o $(OUTPUT_DIR)/$@ $^
install_deps:
	sudo apt-get install libasound-dev
	mkdir -p lib
	cd lib && curl -O -L https://www.portaudio.com/archives/pa_stable_v190600_20161030.tgz
	tar -xzf lib/pa_stable_v190600_20161030.tgz -C lib
	cd lib/portaudio && ./configure && make -j

install_fftw: install_deps
	mkdir -p lib
	curl https://www.fftw.org/fftw-3.3.10.tar.gz | tar -zx -C lib
	cd lib/fftw-3.3.10 && ./configure && $(MAKE) -j && sudo $(MAKE) install

clean:
	rm -f $(OUTPUT_DIR)/$(EXEC) $(GEN)
	rm -f "./test.wav"
