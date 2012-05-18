# qmake project file

QT = core gui

CONFIG += qt resources warn_on shared dll plugin
CONFIG += release
#CONFIG += debug

TARGET   = ../../../bin/lv2/XY-Controller.lv2/XY_Controller
TEMPLATE = lib

SOURCES  = \
    ../source/XY-Controller.cpp \
    ../source/XY-ControllerUi.cpp \
    ../../common/Qt4-Widgets/pixmapdial.cpp \
    ../../common/Qt4-Widgets/pixmapkeyboard.cpp

HEADERS  = \
    ../source/DistrhoPlugin.h \
    ../source/XY-Controller.h \
    ../source/XY-ControllerUi.h \
    ../../common/Qt4-Widgets/pixmapdial.h \
    ../../common/Qt4-Widgets/pixmapkeyboard.h

FORMS    = \
    ../source/xycontroller.ui

RESOURCES = \
    ../../common/Artwork/bitmaps.qrc

INCLUDEPATH = \
    ../source \
    ../../common/Qt4-Widgets

# -----------------------------------------------------------

CONFIG += DISTRHO_PLUGIN_TARGET_LV2
include(../../../libs/distrho-ports/d_src.pri)
