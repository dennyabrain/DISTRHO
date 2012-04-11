# qmake project file

QT = core gui

CONFIG += qt resources warn_on shared dll plugin
CONFIG += release
#CONFIG += debug

TARGET   = ../../../bin/StereoAudioGain.lv2/Stereo_Audio_Gain
TEMPLATE = lib

SOURCES = \
    ../source/StereoAudioGain.cpp \
    ../source/StereoAudioGainUi.cpp \
    ../../common/Qt4-Widgets/digitalpeakmeter.cpp \
    ../../common/Qt4-Widgets/pixmapdial.cpp \

HEADERS = \
    ../source/DistrhoPlugin.h \
    ../source/StereoAudioGain.h \
    ../source/StereoAudioGainUi.h \
    ../../common/Qt4-Widgets/digitalpeakmeter.h \
    ../../common/Qt4-Widgets/pixmapdial.h

HEADERS += \
    ../../../libs/distrho-ports/PluginBase.h \
    ../../../libs/distrho-ports/UiBase.h

FORMS = \
    ../source/StereoAudioGain.ui

RESOURCES = \
    ../../common/Artwork/knobs/knobs.qrc

INCLUDEPATH = \
    ../source \
    ../../common/Qt4-Widgets \
    ../../../libs/distrho-ports

# -----------------------------------------------------------

DEFINES  = DISTRHO_PLUGIN_TARGET_LV2

SOURCES += \
    ../../../libs/distrho-ports/PluginLV2.cpp \
    ../../../libs/distrho-ports/UiLV2.cpp
