# distrho plugin target config

INCLUDEPATH += $$PWD

HEADERS     += $$PWD/PluginBase.h
HEADERS     += $$PWD/UiBase.h

SOURCES     += $$PWD/src/PluginBase.cpp

DISTRHO_PLUGIN_BASE_VST {
SOURCES     += $$PWD/src/d_vst.cpp
}

DISTRHO_PLUGIN_TARGET_JACK {
SOURCES     += $$PWD/src/PluginJACK.cpp
FORMS       += $$PWD/src/PluginJACK.ui
CONFIG      += link_pkgconfig
PKGCONFIG   += jack
}

DISTRHO_PLUGIN_TARGET_LADSPA {
DEFINES     += DISTRHO_PLUGIN_TARGET_LADSPA
SOURCES     += $$PWD/src/PluginLADSPA-DSSI.cpp
}

DISTRHO_PLUGIN_TARGET_DSSI {
DEFINES     += DISTRHO_PLUGIN_TARGET_DSSI
SOURCES     += $$PWD/src/PluginLADSPA-DSSI.cpp
SOURCES     += $$PWD/src/UiDSSI.cpp
CONFIG      += link_pkgconfig
PKGCONFIG   += liblo
}

DISTRHO_PLUGIN_TARGET_LV2 {
DEFINES     += DISTRHO_PLUGIN_TARGET_LV2
SOURCES     += $$PWD/src/PluginLV2.cpp
SOURCES     += $$PWD/src/UiLV2.cpp
}

DISTRHO_PLUGIN_TARGET_VST {
DEFINES     += DISTRHO_PLUGIN_TARGET_VST
SOURCES     += $$PWD/src/PluginVST.cpp
QMAKE_CXXFLAGS *= -fpermissive
}

QMAKE_CXXFLAGS *= -std=c++0x
