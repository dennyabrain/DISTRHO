# qmake project file

QT = core gui

CONFIG += warn_on shared dll plugin
CONFIG += release
#CONFIG += debug

TARGET   = ../../../bin/dssi/StereoAudioGain.so
TEMPLATE = lib

SOURCES  = \
    ../source/StereoAudioGain.cpp

HEADERS = \
    ../source/DistrhoPlugin.h \
    ../source/StereoAudioGain.h

INCLUDEPATH = \
    ../source

# -----------------------------------------------------------

CONFIG += DISTRHO_PLUGIN_TARGET_DSSI
include(../../../libs/distrho-ports/d_src.pri)
