
include(qmake.pri)

CONFIG  += plugin shared

TARGET   = $${NAME}
TEMPLATE = lib

SOURCES  = \
    $${SOURCE_DIR}/DistrhoPlugin3BandEQ.cpp

HEADERS  = \
    $${SOURCE_DIR}/DistrhoPlugin3BandEQ.h \
    $${SOURCE_DIR}/DistrhoPluginInfo.h

SOURCES += \
    $${DISTRHO_DIR}/DistrhoPluginMain.cpp

unix {
    TARGET_LV2   = $${TARGET_DIR}/$${NAME}.$${QMAKE_EXTENSION_SHLIB}
    QMAKE_CLEAN += $${TARGET_LV2}
    QMAKE_POST_LINK += strip $(TARGET);
    QMAKE_POST_LINK += mkdir -p $${TARGET_DIR};
    QMAKE_POST_LINK += $${QMAKE_COPY} -vp $(TARGET) $${TARGET_LV2};
}
