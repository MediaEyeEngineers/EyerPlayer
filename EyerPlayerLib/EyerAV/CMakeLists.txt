include_directories (../)
include_directories (./)

add_library(
    EyerAV
    EyerAVPacket.cpp
    EyerAVReader.cpp
    EyerAVDecoder.cpp
    EyerAVStream.cpp
    EyerAVFrame.cpp
    EyerAVEncoder.cpp
    EyerAVWriter.cpp

    EyerAV.hpp
    EyerAVDecoderPrivate.hpp
    EyerAVEncoderPrivate.hpp
    EyerAVFramePrivate.hpp
    EyerAVPacketPrivate.hpp
    EyerAVReaderPrivate.hpp
    EyerAVStreamPrivate.hpp
    EyerAVWriterPrivate.hpp
    EyerAVBitmap.cpp
    EyerAVRational.cpp
    EyerAVAudioFrameUtil.cpp
    EyerAVFrameWeight.cpp
        EyerAVPacketQueue.cpp
        EyerAVPacketQueue.hpp
        EyerAVFrameQueue.cpp
        EyerAVFrameQueue.hpp
        EyerAVQueue.cpp
        EyerAVQueue.hpp
        EyerAVCropUtil.cpp
        EyerAVQueueManager.hpp
        )

target_link_libraries (EyerAV pthread)
target_link_libraries (EyerAV EyerCore)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/include)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (EyerAV dl)
    target_link_libraries (EyerAV z)
    target_link_libraries (EyerAV bz2)
    target_link_libraries (EyerAV lzma)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (EyerAV z)
    target_link_libraries (EyerAV bz2)
    target_link_libraries (EyerAV ws2_32)
    target_link_libraries (EyerAV Secur32)
    target_link_libraries (EyerAV lzma)
    target_link_libraries (EyerAV iconv)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")

    target_link_libraries (EyerAV bz2)
    target_link_libraries (EyerAV z)
    target_link_libraries (EyerAV lzma)
    target_link_libraries (EyerAV iconv)

    link_directories(${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib)
    link_directories(/Users/lichi/EyerWand/Lib/ffmpeg_install/lib/)

    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)

    # target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.dylib)
    # target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.dylib)
    # target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.dylib)
    # target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.dylib)
    # target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.dylib)
    # target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.dylib)
    # target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.dylib)
    
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)
    
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files 
    EyerAV.hpp
        EyerAVPacketQueue.hpp
        EyerAVFrameQueue.hpp
        EyerAVQueue.hpp
        EyerAVQueueManager.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerAV)
INSTALL(
    TARGETS EyerAV
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

