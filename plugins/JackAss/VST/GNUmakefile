# Compile the VST Plugin

CXX     ?= g++
WINECXX ?= wineg++

BASE_FLAGS    = -shared -O2 -ffast-math -fomit-frame-pointer -fPIC -mtune=generic -msse -mfpmath=sse -std=c++0x -Wall -I../../../sdks/vstsdk2.4 $(CXXFLAGS)
BASE_FLAGS    = -shared -O0 -g -fPIC -std=c++0x -Wall -I../../../sdks/vstsdk2.4 $(CXXFLAGS)

UNIX_FLAGS    = $(BASE_FLAGS) `pkg-config --cflags --libs jack` $(LDFLAGS)

MINGW32_FLAGS = $(BASE_FLAGS) -I/opt/mingw32/include -DPTW32_STATIC_LIB -lpthread -lws2_32
MINGW64_FLAGS = $(BASE_FLAGS) -I/opt/mingw32/include -DPTW32_STATIC_LIB -lpthread -lws2_32

WINE32_FLAGS  = $(UNIX_FLAGS) -fpermissive -m32 -L/usr/lib32/wine -L/usr/lib/i386-linux-gnu/wine
WINE64_FLAGS  = $(UNIX_FLAGS) -fpermissive -m64 -L/usr/lib64/wine -L/usr/lib/x86_64-linux-gnu/wine

all: build

build:   ../../../bin/vst/JackAss.so
mingw32: ../../../bin/vst/JackAss32.dll
mingw64: ../../../bin/vst/JackAss64.dll
wine32:  ../../../bin/vst/JackAssWine32.dll
wine64:  ../../../bin/vst/JackAssWine64.dll

../../../bin/vst/JackAss.so: ../source/jackass.cpp
	$(CXX) $^ $(UNIX_FLAGS) -o $@

../../../bin/vst/JackAss32.dll: ../source/jackass.cpp
	$(CXX) $^ windows.def $(MINGW32_FLAGS) -o $@

../../../bin/vst/JackAss64.dll: ../source/jackass.cpp
	$(CXX) $^ windows.def $(MINGW32_FLAGS) -o $@

../../../bin/vst/JackAssWine32.dll: ../source/jackass.cpp
	$(WINECXX) $^ windows.def $(WINE32_FLAGS) -o $@
	mv $@.so $@

../../../bin/vst/JackAssWine64.dll: ../source/jackass.cpp
	$(WINECXX) $^ windows.def $(WINE64_FLAGS) -o $@
	mv $@.so $@

clean:
	rm -f ../../../bin/vst/JackAss*
