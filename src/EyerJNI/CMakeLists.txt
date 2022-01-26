INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY(
        EyerJNI

        EyerJNIHeader.hpp

        EyerJNIEnv.hpp
        EyerJNIEnv.cpp

        EyerJNIObject.hpp
        EyerJNIObject.cpp

        EyerJNIEnvManager.hpp
        EyerJNIEnvManager.cpp
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

SET(head_files
        EyerJNIHeader.hpp
        EyerJNIEnv.hpp
        EyerJNIObject.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerJNI)
INSTALL(
        TARGETS EyerJNI
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
