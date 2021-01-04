include_directories (../)
include_directories (./)

add_library(
        EyerNet
        EyerNet.cpp
        EyerSimplestHttp.cpp
        EyerHttpTask.cpp
        EyerHttpPool.cpp EyerHttpPool.hpp)

target_link_libraries (
        EyerNet
        EyerCore
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

set(head_files
        EyerNet.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerNet)
INSTALL(
        TARGETS EyerNet
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

