include_directories (../)
include_directories (./)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/include)
include_directories (../EyerGLAD/glad/include/)

add_library(
        EyerGL
        EyerGL.hpp
        EyerGLShader.cpp
        EyerGLProgram.cpp
        EyerGLVAO.cpp
        EyerGLDraw.cpp
        EyerGLTexture.cpp
        EyerGLFrameBuffer.cpp
        EyerGLComponent.cpp
        )

target_link_libraries (EyerGL EyerCore)
target_link_libraries (EyerGL pthread)
target_link_libraries (EyerGL gtest)
target_link_libraries (EyerGL EyerGLAD)
target_link_libraries (EyerGL ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        MESSAGE(STATUS "current platform: Linux")
        target_link_libraries (EyerGL dl)
        target_link_libraries (EyerGL X11)
        target_link_libraries (EyerGL bz2)
        target_link_libraries (EyerGL z)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        MESSAGE(STATUS "current platform: Windows")
        target_link_libraries (EyerGL bz2)
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
