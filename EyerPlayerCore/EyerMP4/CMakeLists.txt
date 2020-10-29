include_directories (../)
include_directories (./)

add_library(
        EyerMP4
        EyerMP4.hpp
        MP4Box.cpp
        MP4Box.hpp
        BoxType.cpp
        BoxType.hpp
        MP4BoxFTYP.cpp
        MP4BoxFTYP.hpp
        MP4File.cpp
        MP4File.hpp
        MP4BoxMVHD.cpp
        MP4BoxMVHD.hpp
        MP4FullBox.cpp
        MP4FullBox.hpp
        MP4BoxTKHD.cpp
        MP4BoxTKHD.hpp
        EyerISOTypeReader.cpp
        EyerISOTypeReader.hpp
        MP4Stream.cpp
        MP4Stream.hpp
        MP4BoxELST.cpp
        MP4BoxELST.hpp
        MP4BoxHDLR.cpp
        MP4BoxHDLR.hpp
        MP4BoxDREF.cpp
        MP4BoxDREF.hpp
        MP4BoxURL.cpp
        MP4BoxURL.hpp
        MP4BoxURN.cpp
        MP4BoxURN.hpp
        MP4BoxTREX.cpp
        MP4BoxTREX.hpp
        MP4BoxMEHD.cpp
        MP4BoxMEHD.hpp
        MP4BoxSTSD.cpp
        MP4BoxSTSD.hpp
        MP4BoxAVC1.cpp
        MP4BoxAVC1.hpp
        MP4BoxSampleEntry.cpp
        MP4BoxSampleEntry.hpp
        MP4BoxAVCC.cpp
        MP4BoxAVCC.hpp
        MP4BoxSTTS.cpp
        MP4BoxSTTS.hpp
        MP4BoxSTSC.cpp
        MP4BoxSTSC.hpp
        MP4BoxSTCO.cpp
        MP4BoxSTCO.hpp
)

target_link_libraries (
        EyerCore
)

set(head_files
        EyerMP4.hpp
        MP4Box.hpp
        BoxType.hpp
        MP4BoxFTYP.hpp
        MP4BoxFTYP.hpp
        MP4File.hpp
        MP4BoxMVHD.hpp
        MP4FullBox.hpp
        MP4BoxTKHD.hpp
        EyerISOTypeReader.hpp
        MP4Stream.hpp
        MP4BoxELST.hpp
        MP4BoxHDLR.hpp
        MP4BoxDREF.hpp
        MP4BoxURL.hpp
        MP4BoxURL.hpp
        MP4BoxURN.hpp
        MP4BoxTREX.hpp
        MP4BoxMEHD.hpp
        MP4BoxSTSD.hpp
        MP4BoxAVC1.hpp
        MP4BoxSampleEntry.hpp
        MP4BoxAVCC.hpp
        MP4BoxSTTS.hpp
        MP4BoxSTSC.hpp
        MP4BoxSTCO.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerMP4)
INSTALL(
        TARGETS EyerMP4
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

