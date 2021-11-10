QT       += core gui multimedia opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += EYER_PLATFORM_QT

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../Lib/EyerPlayer_install/include

LIBS += -L$$PWD/../Lib/EyerPlayer_install/lib -lEyerPlayer -lEyerColorSpace -lEyerGL -lEyerEvent -lEyerDeocdeQueue -lEyerAV -lEyerMath -lEyerCore -lEyerThread
LIBS += -L$$PWD/../Lib/ffmpeg_install/lib -lavformat -lavcodec -lswscale -lswresample -lavutil

LIBS += -framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration
LIBS += -lz -llzma -lbz2 -liconv

SOURCES += \
    EyerPlayerRenderThread.cpp \
    EyerPlayerWidget.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    EyerPlayerRenderThread.h \
    EyerPlayerWidget.h \
    MainWindow.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
