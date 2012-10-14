
include(qmake.pri)

CONFIG  += plugin shared

TARGET   = $${NAME}
TEMPLATE = lib

SOURCES  = \
    $${SOURCE_DIR}/DistrhoArtwork.cpp \
    $${SOURCE_DIR}/DistrhoPluginPingPongPan.cpp \
    $${SOURCE_DIR}/DistrhoUIPingPongPan.cpp

HEADERS  = \
    $${SOURCE_DIR}/DistrhoPluginInfo.h \
    $${SOURCE_DIR}/DistrhoPluginPingPongPan.h \
    $${SOURCE_DIR}/DistrhoUIPingPongPan.h

SOURCES += \
    $${DISTRHO_DIR}/DistrhoPluginMain.cpp \
    $${DISTRHO_DIR}/DistrhoUIMain.cpp

LIBS = -lGL

unix {
    TARGET_VST   = $${TARGET_DIR}/$${NAME}.$${QMAKE_EXTENSION_SHLIB}
    QMAKE_CLEAN += $${TARGET_VST}
    QMAKE_POST_LINK += strip $(TARGET);
    QMAKE_POST_LINK += mkdir -p $${TARGET_DIR};
    QMAKE_POST_LINK += $${QMAKE_COPY} -vp $(TARGET) $${TARGET_VST};
}
