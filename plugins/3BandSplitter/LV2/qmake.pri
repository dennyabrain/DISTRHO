
isEmpty(QMAKE_EXTENSION_SHLIB) {
    QMAKE_EXTENSION_SHLIB = so
}

NAME = 3BandSplitter

DISTRHO_DIR = ../../../libs/distrho
SOURCE_DIR  = ../source
TARGET_DIR  = ../../../bin/lv2/d-3bandsplitter.lv2

CONFIG  = release warn_on
DEFINES = DISTRHO_PLUGIN_TARGET_LV2

INCLUDEPATH = \
    $${DISTRHO_DIR} \
    $${SOURCE_DIR}

QMAKE_CXXFLAGS *= -ffast-math -fomit-frame-pointer -mtune=generic -msse -mfpmath=sse
QMAKE_CXXFLAGS *= -fvisibility=hidden -fPIC
QMAKE_CXXFLAGS *= -std=c++0x
