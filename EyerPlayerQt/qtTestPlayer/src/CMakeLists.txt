
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories(../)
include_directories(../3rdpart/glad/include)
include_directories(../3rdpart/glfw/include)



link_directories(../3rdpart/ffmpge/lib)
link_directories(../3rdpart/glfw/lib)

set(QRC_SOURCE_FILES rec.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

add_executable(
    myWindow
    ${QRC_FILES}
    main.cpp
    widget.cpp
    widget.h
    winopenglwidget.h
    winopenglwidget.cpp
    signalplayer.h
    signalplayer.cpp
    widget.ui
)

target_link_libraries(myWindow Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(myWindow MMThread)
target_link_libraries(myWindow MMAV)
target_link_libraries(myWindow MMPlayer)
target_link_libraries(myWindow MMPlayOpenGL)

# 链接ffmpeg的库
target_link_libraries(myWindow avcodec)
target_link_libraries(myWindow avdevice)
target_link_libraries(myWindow avfilter)
target_link_libraries(myWindow avformat)
target_link_libraries(myWindow avutil)
target_link_libraries(myWindow swresample)
target_link_libraries(myWindow swscale)
