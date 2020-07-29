include_directories (../)
include_directories (./)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_include/include)
include_directories (${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/include)
include_directories (../EyerGLAD/glad/include/)

add_library(
        EyerGL

        GLHeader.h
        EyerGL.hpp
        EyerGLShader.cpp
        EyerGLProgram.cpp
        EyerGLVAO.cpp
        EyerGLDraw.cpp
        EyerGLTexture.cpp
        EyerGLFrameBuffer.cpp
        EyerGLComponent.cpp
        EyerGLRenderTask.cpp
        EyerGLRenderTaskQueue.cpp
        )

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
        EyerGL.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerGL)
INSTALL(
        TARGETS EyerGL
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
