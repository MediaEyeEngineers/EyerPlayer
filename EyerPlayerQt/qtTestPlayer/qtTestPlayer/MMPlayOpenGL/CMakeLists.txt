# CMakeList.txt: MMPlayOpenGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)



include_directories(../3rdpart/glad/include)
include_directories(../3rdpart/glfw/include)
include_directories(../)

link_directories(../3rdpart/glfw/lib/)


# 将源代码添加到此项目的可执行文件。
add_library (
	MMPlayOpenGL 
	../3rdpart/stbimage/stb_image.cpp
	"MMOpenGLThread.cpp"
	
)

target_link_libraries(MMPlayOpenGL glfw3.lib)
target_link_libraries(MMPlayOpenGL MMGL)
# TODO: 如有需要，请添加测试并安装目标。
