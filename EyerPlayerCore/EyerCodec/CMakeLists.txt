include_directories (../)
include_directories (./)

add_library(
        EyerCodec
        EyerMediaCodec2.cpp
        EyerMediaCodec.cpp
)

set(head_files 
        EyerCodec.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerCodec)
INSTALL(
        TARGETS EyerCodec
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
