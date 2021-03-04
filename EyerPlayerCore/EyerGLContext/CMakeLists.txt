include_directories (../)
include_directories (./)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        MESSAGE(STATUS "current platform: Linux")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        MESSAGE(STATUS "current platform: Windows")
        add_library(
                EyerGLContext
                EyerGLContextThread_Windows.cpp)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
        MESSAGE(STATUS "current platform: Android")
        add_library(
                EyerGLContext
# <<<<<<< Updated upstream
                EyerGLContextThread_Android.cpp)
# =======

#                EyerGLContextThread.cpp)
# >>>>>>> Stashed changes

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        MESSAGE(STATUS "current platform: Darwin")
        add_library(
                EyerGLContext
                EyerGLContextThread_Windows.cpp)
ELSE ()
        MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files
        EyerGLContext.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerGLContext)
INSTALL(
        TARGETS EyerGLContext
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
