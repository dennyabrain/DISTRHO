#!/usr/bin/make -f

CXX ?= g++
MOC ?= moc

BUILD_FLAGS  = -O2 -ffast-math -fomit-frame-pointer -fvisibility=hidden -fPIC -mtune=generic -msse -mfpmath=sse -std=c++0x -Wall $(CXXFLAGS)
BUILD_FLAGS  = -O0 -g -fPIC -std=c++0x -Wall $(CXXFLAGS)
BUILD_FLAGS += -I../source -I../../../libs/distrho
BUILD_FLAGS += -DDISTRHO_PLUGIN_TARGET_DSSI

BUILD_PLUGIN_FLAGS = $(BUILD_FLAGS) -shared
BUILD_UI_FLAGS     = $(BUILD_FLAGS) $(shell pkg-config --cflags --libs liblo QtCore QtGui)

PLUGIN_OBJ = \
	../source/DistrhoPluginNotes.cpp

UI_OBJ     = \
	../source/DistrhoUINotes.cpp \
	../source/ParamProgressBar.cpp

UI_FILES   = \
	../source/moc_DistrhoUINotes.cpp \
	../source/moc_ParamProgressBar.cpp

# -------------------------------------------------

TARGET_DIR = ../../../bin/dssi

TARGETS = \
	$(TARGET_DIR)/d-notes.so \
	$(TARGET_DIR)/d-notes/d-notes_qt4

# -------------------------------------------------

all: $(TARGETS)

$(TARGET_DIR)/d-notes.so: $(PLUGIN_OBJ)
	mkdir -p $(TARGET_DIR)
	$(CXX) $^ $(BUILD_PLUGIN_FLAGS) -o $@

$(TARGET_DIR)/d-notes/d-notes_qt4: $(UI_OBJ) $(UI_FILES)
	mkdir -p $(TARGET_DIR)/d-notes
	$(CXX) $^ $(BUILD_UI_FLAGS) -o $@

clean:
	rm -f $(TARGETS) $(UI_FILES)

# -------------------------------------------------

../source/moc_DistrhoUINotes.cpp: ../source/DistrhoUINotes.h
	$(MOC) $< -o $@

../source/moc_ParamProgressBar.cpp: ../source/ParamProgressBar.h
	$(MOC) $< -o $@
