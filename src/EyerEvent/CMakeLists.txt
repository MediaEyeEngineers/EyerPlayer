INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY (
        EyerEvent

        EyerEventHeader.hpp

        Event.hpp
        Event.cpp

        EventRequest.hpp
        EventRequest.cpp

        EventResponse.hpp
        EventResponse.cpp

        EventRequest_Play.hpp
        EventRequest_Play.cpp

        EventRequest_Stop.hpp
        EventRequest_Stop.cpp

        EventRequest_Pause.hpp
        EventRequest_Pause.cpp

        EventRequest_Resume.hpp
        EventRequest_Resume.cpp
)

SET(HEAD_FILES
        EyerEventHeader.hpp
        )

INSTALL(FILES ${HEAD_FILES} DESTINATION include/EyerEvent)
INSTALL(
        TARGETS EyerEvent
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
