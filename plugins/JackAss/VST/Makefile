# Compile the VST Plugin

BUILD_FLAGS = -O2 -shared -fPIC -fvisibility=hidden -Wall -I../../../sdks/vstsdk2.4 `pkg-config --cflags jack` $(CXX_FLAGS)
LINK_FLAGS  = `pkg-config --libs jack` $(LDD_FLAGS)

WINECXX    ?= wineg++
WINE_FLAGS  = -m32

all: build

build: ../../../bin/jackass.so
wine: ../../../bin/jackass.dll

../../../bin/jackass.so: ../source/jackass.cpp
	$(CXX) $(BUILD_FLAGS) $< -o $@ $(LINK_FLAGS)

../../../bin/jackass.dll: ../source/jackass.cpp
	$(WINECXX)  $(BUILD_FLAGS) $(WINE_FLAGS) $< wine.def -o $@ $(LINK_FLAGS)
	mv $@.so $@

clean:
	rm -f ../../../bin/jackass.so ../../../bin/jackass.dll
