include_directories (../)
include_directories (./)

add_library(
        EyerGL

        GLHeader.hpp
        EyerGL.hpp

        EyerGLShader.hpp
        EyerGLShader.cpp

        EyerGLProgram.hpp
        EyerGLProgram.cpp

        EyerGLDraw.hpp
        EyerGLDraw.cpp

        EyerGLComponent.hpp
        EyerGLComponent.cpp

        EyerGLTexture.hpp
        EyerGLTexture.cpp

        EyerGLFrameBuffer.hpp
        EyerGLFrameBuffer.cpp

        EyerGLVAO.hpp
        EyerGLVAO.cpp

        EyerTextureCache.hpp
        EyerTextureCache.cpp

        EyerGLFrameBufferParams.hpp
        EyerGLFrameBufferParams.cpp
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

        GLHeader.hpp

        EyerGLShader.hpp
        EyerGLProgram.hpp
        EyerGLDraw.hpp
        EyerGLComponent.hpp
        EyerGLTexture.hpp
        EyerGLFrameBuffer.hpp
        EyerGLComponent.hpp
        EyerGLTextureType.hpp
        EyerTextureCache.hpp
        EyerGLVAO.hpp
        EyerGLDrawType.hpp
        EyerGLFrameBufferParams.hpp
        OpenGLFunctionsContext.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerGL)
INSTALL(
        TARGETS EyerGL
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
