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

                EyerGLContextThreadAndroid.cpp

                EyerGLTestComponent.hpp
                EyerGLTestComponent.cpp
        )

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        MESSAGE(STATUS "current platform: Darwin")
        add_library(
                EyerGLContext
                EyerGLContextThread_Windows.cpp)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "iOS")
        MESSAGE(STATUS "current platform: iOS")
        add_library(
                EyerGLContext
                EyerGL_IOS_Context_C_Interface.h
                EyerGL_IOS_Context_C_Interface.mm
                EyerGLContextThreadIOS.cpp
                EyerGLTestComponent.hpp
                EyerGLTestComponent.cpp
        )

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
