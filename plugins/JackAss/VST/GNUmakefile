# Compile the VST Plugin

CXX     ?= g++
WINECXX ?= wineg++

BUILD_FLAGS = -shared -O2 -mtune=generic -msse -ffast-math -fpermissive -fomit-frame-pointer -fvisibility=hidden -fPIC -std=c++0x -Wall -I../../../sdks/vstsdk2.4 $(CXXFLAGS)
UNIX_FLAGS  = `pkg-config --cflags --libs jack` $(LDFLAGS)
MINGW_FLAGS = -I/opt/mingw32/include -I"$(HOME)/.wine/drive_c/Program Files (x86)/Jack/includes/" "$(HOME)/.wine/drive_c/Program Files (x86)/Jack/lib/libjack.lib" /opt/mingw32/lib/libpthread.a -lws2_32 -DPTW32_STATIC_LIB
WINE_FLAGS  = -m32 -L/usr/lib32/wine -L/usr/lib/i386-linux-gnu/wine

all: build

build: ../../../bin/vst/JackAss.so
mingw: ../../../bin/vst/JackAss.dll
wine:  ../../../bin/vst/JackAssWine.dll

../../../bin/vst/JackAss.so: ../source/jackass.cpp
	$(CXX) $(BUILD_FLAGS) $(UNIX_FLAGS) $< -o $@

../../../bin/vst/JackAss.dll: ../source/jackass.cpp
	$(CXX) $(BUILD_FLAGS) $< windows.def $(MINGW_FLAGS) -o $@

../../../bin/vst/JackAssWine.dll: ../source/jackass.cpp
	$(WINECXX) $(BUILD_FLAGS) $(UNIX_FLAGS) $(WINE_FLAGS) $< windows.def -o $@
	mv $@.so $@

clean:
	rm -f ../../../bin/vst/JackAss*
