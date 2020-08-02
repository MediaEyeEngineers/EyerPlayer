include_directories (../)
include_directories (./)

add_executable(
        EyerPlayerMain
        Main.cpp
)

target_link_libraries (
        EyerPlayerMain
        EyerPlayer
        EyerAV
        EyerEventQueue
        EyerGLContext
        EyerGL
        EyerCore
        EyerThread
)