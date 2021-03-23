cmake_minimum_required(VERSION 3.5)

project(qtTestPlayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()


#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

## 包含头文件
#include_directories(3rdpart/player/include)

#link_directories(3rdpart/player/lib)
#link_directories(3rdpart/ffmpge/lib)
#link_directories(3rdpart/glfw/lib)



#if(ANDROID)
#  add_library(qtTestPlayer SHARED
#    main.cpp
#    widget.cpp
#    widget.h
#    widget.ui
#  )
#else()
#  add_executable(qtTestPlayer
#    main.cpp
#    widget.cpp
#    widget.h
#    winopenglwidget.h
#    winopenglwidget.cpp
#    signalplayer.h
#    signalplayer.cpp
#    widget.ui
#  )
#endif()

project ("qtTestPlayer")

add_subdirectory("src")
add_subdirectory ("MMPlayer")
add_subdirectory ("MMThread")
add_subdirectory ("MMAV")
add_subdirectory ("MMGL")
add_subdirectory ("MMPlayOpenGL")


#target_link_libraries(qtTestPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(qtTestPlayer PRIVATE MMAV)
#target_link_libraries(qtTestPlayer PRIVATE MMGL)
#target_link_libraries(qtTestPlayer PRIVATE MMPlayer)
#target_link_libraries(qtTestPlayer PRIVATE MMPlayOpenGL)
#target_link_libraries(qtTestPlayer PRIVATE MMThread)

## ffmpge
#target_link_libraries(qtTestPlayer PRIVATE avutil)
#target_link_libraries(qtTestPlayer PRIVATE postproc)
#target_link_libraries(qtTestPlayer PRIVATE swresample)
#target_link_libraries(qtTestPlayer PRIVATE swscale)
#target_link_libraries(qtTestPlayer PRIVATE avcodec)
#target_link_libraries(qtTestPlayer PRIVATE avdevice)
#target_link_libraries(qtTestPlayer PRIVATE avfilter)
#target_link_libraries(qtTestPlayer PRIVATE avformat)
#target_link_libraries(qtTestPlayer PRIVATE glfw3.lib)
