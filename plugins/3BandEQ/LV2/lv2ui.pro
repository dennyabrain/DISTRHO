
include(qmake.pri)

CONFIG  += plugin shared

TARGET   = $${NAME}_ui
TEMPLATE = lib

SOURCES  = \
    $${SOURCE_DIR}/DistrhoArtwork.cpp \
    $${SOURCE_DIR}/DistrhoUI3BandEQ.cpp

HEADERS +=  \
    $${SOURCE_DIR}/DistrhoPluginInfo.h \
    $${SOURCE_DIR}/DistrhoUI3BandEQ.h

SOURCES += \
    $${DISTRHO_DIR}/DistrhoUIMain.cpp

LIBS = -lGL

unix {
    TARGET_LV2   = $${TARGET_DIR}/$${NAME}_ui.$${QMAKE_EXTENSION_SHLIB}
    QMAKE_CLEAN += $${TARGET_LV2}
    QMAKE_POST_LINK += strip $(TARGET);
    QMAKE_POST_LINK += mkdir -p $${TARGET_DIR};
    QMAKE_POST_LINK += $${QMAKE_COPY} -vp $(TARGET) $${TARGET_LV2};
}
