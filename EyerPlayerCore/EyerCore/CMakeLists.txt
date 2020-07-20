include_directories (../)
include_directories (./)

add_library(
    EyerCore
    # SHARED

    EyerCore.hpp
    EyerString.hpp
    EyerLog.hpp
    EyerLog.cpp
    EyerMath.hpp
    EyerString.cpp

    EyerMat.cpp
    EyerMat4x4.cpp
    EyerMat4x1.cpp
    EyerMat3x1.cpp
    EyerMat2x1.cpp
    EyerRand.cpp
    EyerTime.cpp

    EyerLRUMap.hpp
    EyerLockQueue.hpp

    EyerTime.hpp
)

set(head_files 
    EyerString.hpp
    EyerCore.hpp
    EyerLog.hpp
    EyerMath.hpp
    EyerTime.hpp
    EyerLinkedList.hpp
    EyerLinkedEle.hpp
    EyerQueue.hpp
    EyerMap.hpp
    EyerMapEle.hpp
    EyerLockQueue.hpp
    EyerLRUMap.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerCore)
INSTALL(
    TARGETS EyerCore
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
