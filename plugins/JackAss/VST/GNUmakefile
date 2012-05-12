# Compile the VST Plugin

BUILD_FLAGS = -shared -O2 -mtune=generic -msse -ffast-math -fpermissive -fomit-frame-pointer -fvisibility=hidden -fPIC -std=c++0x -Wall -I../../../sdks/vstsdk2.4 `pkg-config --cflags jack` $(CXX_FLAGS)
LINK_FLAGS  = `pkg-config --libs jack` $(LDD_FLAGS)

WINECXX       ?= wineg++
WINECXX_FLAGS ?= -m32 -L/usr/lib32/wine -L/usr/lib/i386-linux-gnu/wine

all: build

build: ../../../bin/vst/JackAss.so
wine: ../../../bin/vst/JackAss.dll

../../../bin/vst/JackAss.so: ../source/jackass.cpp
	$(CXX) $(BUILD_FLAGS) $< -o $@ $(LINK_FLAGS)

../../../bin/vst/JackAss.dll: ../source/jackass.cpp
	$(WINECXX) $(BUILD_FLAGS) $(WINECXX_FLAGS) $< wine.def -o $@ $(LINK_FLAGS)
	mv $@.so $@

clean:
	rm -f ../../../bin/vst/JackAss.*
