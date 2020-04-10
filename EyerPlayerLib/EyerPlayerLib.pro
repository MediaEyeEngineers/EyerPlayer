#-------------------------------------------------
#
# Project created by QtCreator 2020-03-24T11:44:13
#
#-------------------------------------------------

QT       += widgets opengl multimedia

QT       -= gui

TARGET = EyerPlayerLib



######## 编译库的时候，把这个加上，把 Demo 的注释了 ########
# TEMPLATE = lib


######## 加上以下这些可以编译 Demo ########
TEMPLATE = app

SOURCES += \
        Demo/main.cpp \
        Demo/MainWindow.cpp

HEADERS += \
        Demo/MainWindow.h

FORMS += \
        Demo/MainWindow.ui
######## 加上以上这些可以编译 Demo ########




DEFINES += EYERPLAYERLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_EYER_PLAYER

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        EyerPlayerEventManager.cpp \
        EyerPlayerLib.cpp \
        EyerPlayerVideoRender.cpp \
        EyerPlayerView.cpp \
        AVReaderThread.cpp \
        AVDecoderThread.cpp \
        EventTag.cpp \
        PlayCtrThread.cpp \
        StreamInfo.cpp \
        AudioPlayThread.cpp \
        MediaInfo.cpp

HEADERS += \
        EyerPlayerConstant.h \
        EyerPlayerEventManager.h \
        EyerPlayerLib.h \
        EyerPlayerThread.hpp \
        EyerPlayerVideoRender.h \
        EyerPlayerViewPrivate.h \
        PlayerEvent.hpp \
        PlayerTypedef.hpp \
        eyerplayerlib_global.h


HEADERS += EyerCore/*.hpp
HEADERS += EyerCore/*.h

SOURCES += EyerCore/EyerLog.cpp
SOURCES += EyerCore/EyerMat.cpp
SOURCES += EyerCore/EyerMat2x1.cpp
SOURCES += EyerCore/EyerMat3x1.cpp
SOURCES += EyerCore/EyerMat4x1.cpp
SOURCES += EyerCore/EyerMat4x4.cpp
SOURCES += EyerCore/EyerRand.cpp
SOURCES += EyerCore/EyerString.cpp
SOURCES += EyerCore/EyerTime.cpp


HEADERS += EyerGL/*.hpp
HEADERS += EyerGL/*.h

SOURCES += EyerGL/EyerGLComponent.cpp
SOURCES += EyerGL/EyerGLDraw.cpp
SOURCES += EyerGL/EyerGLFrameBuffer.cpp
SOURCES += EyerGL/EyerGLProgram.cpp
SOURCES += EyerGL/EyerGLShader.cpp
SOURCES += EyerGL/EyerGLTexture.cpp
SOURCES += EyerGL/EyerGLVAO.cpp

HEADERS += EyerThread/*.hpp
HEADERS += EyerThread/*.h

SOURCES += EyerThread/EyerThread.cpp



HEADERS += EyerAV/*.hpp
HEADERS += EyerAV/*.h

SOURCES += EyerAV/EyerAVAudioFrameUtil.cpp
SOURCES += EyerAV/EyerAVBitmap.cpp
SOURCES += EyerAV/EyerAVDecoder.cpp
SOURCES += EyerAV/EyerAVEncoder.cpp
SOURCES += EyerAV/EyerAVFrame.cpp
SOURCES += EyerAV/EyerAVFrameWeight.cpp
SOURCES += EyerAV/EyerAVPacket.cpp
SOURCES += EyerAV/EyerAVRational.cpp
SOURCES += EyerAV/EyerAVReader.cpp
SOURCES += EyerAV/EyerAVStream.cpp
SOURCES += EyerAV/EyerAVWriter.cpp
SOURCES += EyerAV/EyerAVQueue.cpp
SOURCES += EyerAV/EyerAVCropUtil.cpp

HEADERS += EyerEventQueue/*.hpp
HEADERS += EyerEventQueue/*.h

SOURCES += EyerEventQueue/EyerEvent.cpp
SOURCES += EyerEventQueue/EyerEventQueue.cpp

HEADERS += EyerGLShader/*.hpp
HEADERS += EyerGLShader/*.h

SOURCES += EyerGLShader/Shader.cpp

# Lib3rd
INCLUDEPATH += ../Lib3rd/ffmpeg_install/include
LIBS += -L../Lib3rd/ffmpeg_install/lib/ -lavcodec
LIBS += -L../Lib3rd/ffmpeg_install/lib/ -lavdevice
LIBS += -L../Lib3rd/ffmpeg_install/lib/ -lavfilter
LIBS += -L../Lib3rd/ffmpeg_install/lib/ -lavformat
LIBS += -L../Lib3rd/ffmpeg_install/lib/ -lavutil
LIBS += -L../Lib3rd/ffmpeg_install/lib/ -lswresample

unix {
    target.path = /usr/lib
    INSTALLS += target
}
