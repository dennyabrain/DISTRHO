
include(qmake.pri)

QT = core gui

CONFIG   += link_pkgconfig qt
PKGCONFIG = liblo

TARGET   = $${NAME}_gl
TEMPLATE = app

SOURCES  = \
    $${SOURCE_DIR}/DistrhoArtwork.cpp \
    $${SOURCE_DIR}/DistrhoUI3BandSplitter.cpp

HEADERS +=  \
    $${SOURCE_DIR}/DistrhoPluginInfo.h \
    $${SOURCE_DIR}/DistrhoUI3BandSplitter.h

SOURCES += \
    $${DISTRHO_DIR}/DistrhoUIMain.cpp

LIBS = -lGL

unix {
    TARGET_DSSI  = $${TARGET_DIR}/$${NAME}/$${TARGET}
    QMAKE_CLEAN += $${TARGET_DSSI}
    QMAKE_POST_LINK += strip $(TARGET);
    QMAKE_POST_LINK += mkdir -p $${TARGET_DIR}/$${NAME};
    QMAKE_POST_LINK += $${QMAKE_COPY} -vp $(TARGET) $${TARGET_DSSI};
}
