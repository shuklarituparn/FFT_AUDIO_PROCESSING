EXEC = cppaudiocapture
GEN=cppaudiogenerate

CLIB = -I./lib/portaudio/include ./lib/portaudio/lib/.libs/libportaudio.a \
	-lrt -lasound -ljack -pthread -I./lib/fftw-3.3.10/api -lfftw3

$(EXEC): main.cpp
	g++ -o $@ $^ $(CLIB)

$(GEN): make_audio.cpp
	g++ -o $@ $^

install-deps:
	mkdir -p lib
	wget -O portaudio.tgz http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
	tar -zxvf portaudio.tgz -C lib --strip-components=1
	cd lib/portaudio && ./configure && $(MAKE) -j
	rm portaudio.tgz
.PHONY: install-deps


uninstall-deps:
	cd lib/portaudio && $(MAKE) uninstall
	rm -rf lib/portaudio
.PHONY: uninstall-deps

clean:
	rm -f $(EXEC)
.PHONY: clean
