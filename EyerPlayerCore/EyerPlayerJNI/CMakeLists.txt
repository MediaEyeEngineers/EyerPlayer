include_directories (../)
include_directories (./)

link_directories(${CMAKE_SOURCE_DIR}/../Lib/ffmpeg_install/lib)

add_library(
    EyerPlayerJNI
    SHARED
    JniUtil.cpp
    EyerPlayerGLContext.cpp
    EyerPlayerJNI.cpp
)

target_link_libraries (EyerPlayerJNI
    EyerPlayer
    EyerAV
    EyerEventQueue
    EyerGLRenderTask
    EyerGLContext
    EyerGL

    EyerThread
    EyerGLShader
    EyerJNI
        EyerCodec
        EyerAV
        EyerCore

    avformat
    avcodec
    swresample
    swscale
    avutil

    log
    z
    android
    OpenSLES
    GLESv3
    EGL
    jnigraphics
)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
    TARGETS EyerPlayerJNI
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)