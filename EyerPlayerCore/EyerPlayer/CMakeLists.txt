include_directories (../)
include_directories (./)
include_directories (../EyerAV)

add_library(
    EyerPlayer
    EyerPlayer.cpp
    EyerPlayerEventManager.cpp
    EventTag.cpp

    AVReaderThread.cpp
    AVDecoderThread.cpp
    AVPlayCtrThread.cpp
        AVDecoderThreadSoftware.cpp
        AVDecoderThreadMediaCodec.cpp

    MediaInfo.cpp
    StreamInfo.cpp

    EyerPlayerThreadManager.cpp

        AVFrameQueueManager.cpp
    )

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files
    EyerPlayer.hpp
    )

INSTALL(FILES ${head_files} DESTINATION include/EyerPlayer)
INSTALL(
    TARGETS EyerPlayer
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
