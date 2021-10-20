INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY (
        EyerDeocdeQueue

        EyerDecodeQueueHeader.hpp

        EyerDeocdeQueue.hpp
        EyerDeocdeQueue.cpp

        EyerDeocdeQueueFFmpeg.hpp
        EyerDeocdeQueueFFmpeg.cpp

        FFmpegDecodeThread.hpp
        FFmpegDecodeThread.cpp
)

SET(HEAD_FILES
        EyerDecodeQueueHeader.hpp
        EyerDeocdeQueue.hpp
        EyerDeocdeQueueFFmpeg.hpp
        )

INSTALL(FILES ${HEAD_FILES} DESTINATION include/EyerDeocdeQueue)
INSTALL(
        TARGETS EyerDeocdeQueue
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
