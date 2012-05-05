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
CONFIG      += link_pkgconfig
PKGCONFIG   += jack
}

DISTRHO_PLUGIN_TARGET_LADSPA {
SOURCES     += $$PWD/src/PluginLADSPA.cpp
}

DISTRHO_PLUGIN_TARGET_LV2 {
SOURCES     += $$PWD/src/PluginLV2.cpp
SOURCES     += $$PWD/src/UiLV2.cpp
}

QMAKE_CXXFLAGS *= --std=c++0x
