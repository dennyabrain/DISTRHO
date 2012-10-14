
include(qmake.pri)

CONFIG  += plugin shared

TARGET   = $${NAME}
TEMPLATE = lib

SOURCES  = \
    $${SOURCE_DIR}/DistrhoPlugin3BandSplitter.cpp

HEADERS  = \
    $${SOURCE_DIR}/DistrhoPlugin3BandSplitter.h \
    $${SOURCE_DIR}/DistrhoPluginInfo.h

SOURCES += \
    $${DISTRHO_DIR}/DistrhoPluginMain.cpp

unix {
    TARGET_DSSI  = $${TARGET_DIR}/$${NAME}.$${QMAKE_EXTENSION_SHLIB}
    QMAKE_CLEAN += $${TARGET_DSSI}
    QMAKE_POST_LINK += strip $(TARGET);
    QMAKE_POST_LINK += mkdir -p $${TARGET_DIR};
    QMAKE_POST_LINK += $${QMAKE_COPY} -vp $(TARGET) $${TARGET_DSSI};
}
