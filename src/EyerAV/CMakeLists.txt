include_directories (../)
include_directories (./)
include_directories (../EyerAV)

include_directories (${CMAKE_SOURCE_DIR}/../..//Lib/ffmpeg_install/include)

add_library(
        EyerAV
        EyerAV.hpp

        EyerAVReader.hpp
        EyerAVReader.cpp

        EyerAVPacket.hpp
        EyerAVPacket.cpp

        EyerAVStream.hpp
        EyerAVStream.cpp

        EyerAVDecoder.hpp
        EyerAVDecoder.cpp

        EyerAVFrame.hpp
        EyerAVFrame.cpp

        EyerAVEncoder.hpp
        EyerAVEncoder.cpp

        EyerAVEncoderParam.hpp
        EyerAVEncoderParam.cpp

        EyerAVRational.hpp
        EyerAVRational.cpp

        EyerAVWriter.hpp
        EyerAVWriter.cpp

        EyerAVBitstreamFilter.hpp
        EyerAVBitstreamFilter.cpp

        EyerAVBitstreamFilterType.hpp
        EyerAVBitstreamFilterType.cpp

        EyerAVDecoderLine.hpp
        EyerAVDecoderLine.cpp

        EyerAVDecoderBox.hpp
        EyerAVDecoderBox.cpp

        EyerAVSampleFormat.hpp
        EyerAVSampleFormat.cpp

        EyerAVADTSUtil.hpp
        EyerAVADTSUtil.cpp

        EyerAVImageReader.hpp
        EyerAVImageReader.cpp

        EyerAVADTS.hpp
        EyerAVADTS.cpp

        EyerAVPixelFormat.hpp
        EyerAVPixelFormat.cpp

        EyerAVPixelFrame.hpp
        EyerAVPixelFrame.cpp

        EyerAVCSEI.cpp
        EyerAVCSEI.hpp

        EyerAvcC.hpp
        EyerAvcC.cpp

        EyerAnnexBParse.hpp
        EyerAnnexBParse.cpp

        EyerNALUnit.hpp
        EyerNALUnit.cpp

        EyerNALUnitSEI.hpp
        EyerNALUnitSEI.cpp

        EyerAVDecoderBoxGroup.hpp
        EyerAVDecoderBoxGroup.cpp

        EyerAVDecoderLineParams.hpp
        EyerAVDecoderLineParams.cpp

        EyerAVSnapshotTask.hpp
        EyerAVSnapshotTask.cpp
)

target_link_libraries (EyerAV EyerCore)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (EyerAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
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

        EyerAVReader.hpp
        EyerAVStream.hpp
        EyerAVDecoder.hpp
        EyerAVPacket.hpp
        EyerAVFrame.hpp
        EyerAVEncoderParam.hpp
        EyerAVEncoder.hpp
        EyerAVRational.hpp
        EyerAVWriter.hpp
        EyerAVBitstreamFilter.hpp
        EyerAVBitstreamFilterType.hpp
        EyerAVDecoderLine.hpp
        EyerAVDecoderBox.hpp
        EyerAVErrorCode.hpp
        EyerAVSampleFormat.hpp
        EyerAVADTSUtil.hpp
        EyerAVImageReader.hpp
        EyerAVADTS.hpp
        EyerAVPixelFormat.hpp
        EyerAVPixelFrame.hpp
        EyerAVCSEI.hpp
        EyerAvcC.hpp
        EyerAnnexBParse.hpp
        EyerNALUnit.hpp
        EyerNALUnitSEI.hpp
        EyerAVDecoderBoxGroup.hpp
        EyerAVDecoderLineParams.hpp
        EyerAVSnapshotTask.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerAV)
INSTALL(
        TARGETS EyerAV
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

