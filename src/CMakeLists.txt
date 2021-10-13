CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(EyerPlayer VERSION 1.0.0.0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/../Lib/ffmpeg_install/include)

LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/../Lib/ffmpeg_install/lib)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    ADD_DEFINITIONS(-D GRF_PLATFORM_LINUX)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    ADD_DEFINITIONS(-D GRF_PLATFORM_WINDOWS)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
    ADD_DEFINITIONS(-D GRF_PLATFORM_ANDROID)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    ADD_DEFINITIONS(-D GRF_PLATFORM_DARWIN)
    SET(CMAKE_EXE_LINKER_FLAGS
            "-framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
            )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "iOS")
    MESSAGE(STATUS "current platform: iOS")
    ADD_DEFINITIONS(-D GRF_PLATFORM_IOS)
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

ADD_SUBDIRECTORY(EyerCore)
ADD_SUBDIRECTORY(EyerThread)
ADD_SUBDIRECTORY(EyerPlayer)
ADD_SUBDIRECTORY(EyerAV)
ADD_SUBDIRECTORY(EyerEvent)
ADD_SUBDIRECTORY(EyerPlayerTest)