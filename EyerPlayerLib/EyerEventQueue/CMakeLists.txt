include_directories (../)
include_directories (./)

add_library(
        EyerEventQueue
        EyerEventQueue.hpp
        EyerEventQueue.cpp
        EyerEvent.cpp
)

target_link_libraries (EyerEventQueue EyerCore)
target_link_libraries (EyerEventQueue pthread)
target_link_libraries (EyerEventQueue gtest)

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
        EyerEventQueue.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerEventQueue)
INSTALL(
        TARGETS EyerEventQueue
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
