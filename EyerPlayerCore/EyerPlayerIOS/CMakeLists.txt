include_directories (../)
include_directories (./)

add_library(
        EyerPlayerIOS
        SHARED
        EyerPlayerIOS.hpp
        EyerPlayerIOS.cpp
)

set(HEADER_FILES
        EyerPlayerIOS.hpp
)

set(RESOURCE_FILES
        README.md
)

set_target_properties(EyerPlayerIOS PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION A
        MACOSX_FRAMEWORK_IDENTIFIER com.zzsin.eyerplayer
        # MACOSX_FRAMEWORK_INFO_PLIST Info.plist
        # "current version" in semantic format in Mach-O binary file
        VERSION 1.0.0
        # "compatibility version" in semantic format in Mach-O binary file
        SOVERSION 1.0.0
        PUBLIC_HEADER "${HEADER_FILES}"
        RESOURCE      "${RESOURCE_FILES}"
        # XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
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
        EyerPlayerIOS.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerPlayerIOS)

INSTALL(
        TARGETS EyerPlayerIOS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        FRAMEWORK DESTINATION framework
)