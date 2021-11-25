INCLUDE_DIRECTORIES(../)
INCLUDE_DIRECTORIES(./)

ADD_LIBRARY(
    EyerAndroidInterface
    SHARED
    Interface.cpp
)

TARGET_LINK_LIBRARIES(EyerAndroidInterface EyerPlayer)
TARGET_LINK_LIBRARIES(EyerAndroidInterface EyerEvent)
TARGET_LINK_LIBRARIES(EyerAndroidInterface EyerDeocdeQueue)
TARGET_LINK_LIBRARIES(EyerAndroidInterface EyerAV)
TARGET_LINK_LIBRARIES(EyerAndroidInterface EyerCore)
TARGET_LINK_LIBRARIES(EyerAndroidInterface EyerThread)

TARGET_LINK_LIBRARIES(EyerAndroidInterface avformat)
TARGET_LINK_LIBRARIES(EyerAndroidInterface avcodec)
TARGET_LINK_LIBRARIES(EyerAndroidInterface swresample)
TARGET_LINK_LIBRARIES(EyerAndroidInterface swscale)
TARGET_LINK_LIBRARIES(EyerAndroidInterface avutil)

TARGET_LINK_LIBRARIES(EyerAndroidInterface z)
TARGET_LINK_LIBRARIES(EyerAndroidInterface log)

INSTALL(
    TARGETS EyerAndroidInterface
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)