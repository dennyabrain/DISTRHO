# qmake project file

CONFIG  = debug
# CONFIG  = release
CONFIG += warn_on
DEFINES = \
    DISTRHO_PLUGIN_TARGET_LADSPA \
    DISTRHO_PLUGIN_TARGET_DSSI \
    DISTRHO_PLUGIN_TARGET_LV2 \
    DISTRHO_PLUGIN_TARGET_VST

TARGET   = distrho-plugin-toolkit
TEMPLATE = lib #app

SOURCES  = \
    DemoPlugin.cpp \
    DemoUI.cpp \
    DistrhoArtwork.cpp \
    ../src/DistrhoPlugin.cpp \
    ../src/DistrhoPluginLADSPA+DSSI.cpp \
    ../src/DistrhoPluginLV2.cpp \
    ../src/DistrhoUI.cpp \
    ../src/DistrhoUILV2.cpp

HEADERS  = \
    DemoPlugin.h \
    DemoUI.h \
    DistrhoPluginInfo.h \
    ../distrho/DistrhoIncludes.h \
    ../distrho/DistrhoPlugin.h \
    ../distrho/DistrhoPluginUtils.h \
    ../distrho/DistrhoUI.h \
    ../src/DistrhoPluginInternal.h \
    ../src/DistrhoUIInternal.h

INCLUDEPATH = \
    ../distrho \
    ../test

#LIBS = -L/home/falktx/Personal/FOSS/Tests/gltest/pugl/build/ -lpugl-0
LIBS = /home/falktx/Personal/FOSS/Tests/gltest/pugl/build/libpugl-0.a -lGL -lGLU

QMAKE_CXXFLAGS *= -std=c++0x
