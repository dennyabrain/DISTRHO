# qmake project file

QT = core gui

CONFIG += qt resources warn_on shared dll plugin
CONFIG += release
#CONFIG += debug

TARGET   = ../../../bin/StereoAudioGain.so
TEMPLATE = lib

SOURCES  = \
    ../source/StereoAudioGain.cpp \
    ../source/StereoAudioGainUi.cpp \
    ../../common/Qt4-Widgets/digitalpeakmeter.cpp \
    ../../common/Qt4-Widgets/pixmapdial.cpp

HEADERS = \
    ../source/DistrhoPlugin.h \
    ../source/StereoAudioGain.h \
    ../source/StereoAudioGainUi.h \
    ../../common/Qt4-Widgets/digitalpeakmeter.h \
    ../../common/Qt4-Widgets/pixmapdial.h

FORMS    = \
    ../source/StereoAudioGain.ui

RESOURCES = \
    ../../common/Artwork/knobs/knobs.qrc

INCLUDEPATH = \
    ../source \
    ../../common/Qt4-Widgets

# -----------------------------------------------------------

CONFIG += DISTRHO_PLUGIN_TARGET_VST
include(../../../libs/distrho-ports/d_src.pri)
