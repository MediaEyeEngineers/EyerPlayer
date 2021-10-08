INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY (
        EyerPlayer

        EyerPlayer.hpp
        EyerPlayer.cpp

        ThreadReader.hpp
        ThreadReader.cpp

        ThreadDecode.hpp
        ThreadDecode.cpp

        ThreadPlayCtr.hpp
        ThreadPlayCtr.cpp

        ThreadEventLoop.hpp
        ThreadEventLoop.cpp

        EventRequest.hpp
        EventRequest.cpp

        EventResponse.hpp
        EventResponse.cpp

        EventRequest_Play.hpp
        EventRequest_Play.cpp
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
