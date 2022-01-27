INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)
INCLUDE_DIRECTORIES (../EyerAV)

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/include)

ADD_LIBRARY(
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

        EyerAVDecoderBoxGroup.hpp
        EyerAVDecoderBoxGroup.cpp

        EyerAVDecoderLineParams.hpp
        EyerAVDecoderLineParams.cpp

        EyerAVSnapshotTask.hpp
        EyerAVSnapshotTask.cpp

        EyerAVTranscode.hpp
        EyerAVTranscode.cpp

        EyerAVTranscodeParams.hpp
        EyerAVTranscodeParams.cpp

        EyerAVResample.hpp
        EyerAVResample.cpp

        EyerAVChannelLayout.hpp
        EyerAVChannelLayout.cpp

        EyerMediaInfo.hpp
        EyerMediaInfo.cpp

        EyerMediaInfoParse.hpp
        EyerMediaInfoParse.cpp

        EyerAVCodecType.hpp
        EyerAVCodecType.cpp

        EyerAVCodecID.hpp
        EyerAVCodecID.cpp

        EyerImageUtil.hpp
        EyerImageUtil.cpp

        EyerAVSEIUtil.hpp
        EyerAVSEIUtil.cpp

        EyerAVDecoderLineAudio.hpp
        EyerAVDecoderLineAudio.cpp
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

SET(HEAD_FILES
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
        EyerAVDecoderBoxGroup.hpp
        EyerAVDecoderLineParams.hpp
        EyerAVSnapshotTask.hpp
        EyerAVTranscode.hpp
        EyerAVTranscodeParams.hpp
        EyerAVResample.hpp
        EyerAVChannelLayout.hpp
        EyerMediaInfo.hpp
        EyerMediaInfoParse.hpp
        EyerAVCodecType.hpp
        EyerAVCodecID.hpp
        EyerImageUtil.hpp
        EyerAVSEIUtil.hpp
        EyerAVDecoderLineAudio.hpp
)

INSTALL(FILES ${HEAD_FILES} DESTINATION include/EyerAV)
INSTALL(
        TARGETS EyerAV
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

