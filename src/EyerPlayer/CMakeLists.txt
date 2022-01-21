INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY (
        EyerPlayer

        EyerPlayer.hpp
        EyerPlayer.cpp

        ThreadReader.hpp
        ThreadReader.cpp

        ThreadPlayCtr.hpp
        ThreadPlayCtr.cpp

        ThreadEventLoop.hpp
        ThreadEventLoop.cpp

        QueueBox.hpp
        QueueBox.cpp

        DecoderBox.hpp
        DecoderBox.cpp
)

SET(HEAD_FILES
        EyerPlayer.hpp
        QueueBox.hpp
        )

INSTALL(FILES ${HEAD_FILES} DESTINATION include/EyerPlayer)
INSTALL(
        TARGETS EyerPlayer
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
