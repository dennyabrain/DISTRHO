
include(qmake.pri)

TARGET   = $${NAME}_export
TEMPLATE = app

SOURCES  = \
    $${SOURCE_DIR}/DistrhoPluginPingPongPan.cpp

HEADERS  = \
    $${SOURCE_DIR}/DistrhoPluginPingPongPan.h \
    $${SOURCE_DIR}/DistrhoPluginInfo.h

SOURCES += \
    $${DISTRHO_DIR}/DistrhoPluginMain.cpp \
    $${DISTRHO_DIR}/src/DistrhoPluginLV2export.cpp

unix {
    QMAKE_CLEAN += *.ttl $${TARGET_DIR}/*.ttl
    QMAKE_POST_LINK += $${PWD}/$(TARGET);
    QMAKE_POST_LINK += mkdir -p $${TARGET_DIR};
    QMAKE_POST_LINK += $${QMAKE_COPY} -vp *.ttl $${TARGET_DIR};
}
