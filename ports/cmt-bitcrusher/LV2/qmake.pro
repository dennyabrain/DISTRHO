# qmake project file

QT -= core gui

CONFIG  = warn_on shared dll plugin
CONFIG += release
#CONFIG += debug

TARGET   = ../../../bin/Bitcrusher.lv2/Bitcrusher
TEMPLATE = lib

SOURCES  = \
    ../source/BitcrusherEditMain.cpp \
    ../source/Bitcrusher.cpp

HEADERS = \
    ../source/DistrhoPlugin.h \
    ../source/Bitcrusher.hpp

INCLUDEPATH = \
    ../source

# -----------------------------------------------------------

CONFIG += DISTRHO_PLUGIN_TARGET_LV2
include(../../../libs/distrho-ports/d_src.pri)
