INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY (
        EyerPlayer

        EyerPlayer.hpp
        EyerPlayer.cpp

        EventControlThread.hpp
        EventControlThread.cpp

        EyerPlayerContext.hpp
        EyerPlayerContext.cpp

        IOReadThread.hpp
        IOReadThread.cpp

        AVDecodeQueueBox.hpp
        AVDecodeQueueBox.cpp
)

SET(HEAD_FILES
        EyerPlayer.hpp
        )

INSTALL(FILES ${HEAD_FILES} DESTINATION include/EyerPlayer)
INSTALL(
        TARGETS EyerPlayer
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
