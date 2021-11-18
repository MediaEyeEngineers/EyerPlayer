include_directories (../)
include_directories (./)

add_library(
        EyerColorSpace
        EyerColorSpace.cpp
        EyerColorSpaceMat.cpp
)

target_link_libraries (EyerColorSpace EyerCore)

set(head_files
        EyerColorSpace.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerColorSpace)
INSTALL(
        TARGETS EyerColorSpace
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
