include_directories (../)
include_directories (./)

add_library(
        EyerDASH
        # SHARED
        EyerMPD.cpp
        EyerAdaptationSet.cpp
        EyerAdaptationSet.hpp
        EyerSegmentTemplate.cpp
        EyerSegmentTemplate.hpp
        EyerRepresentation.cpp
        EyerRepresentation.hpp
        EyerDASHReader.cpp
        EyerDASHReader.hpp
        EyerDASHReaderThread.cpp
        EyerDASHReaderThread.hpp
)

set(head_files
        EyerDASH.hpp
        EyerMPD.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerDASH)
INSTALL(
        TARGETS EyerDASH
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
