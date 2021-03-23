# CMakeList.txt: MMPlayOpenGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)



include_directories(../3rdpart/glad/include)
include_directories(../3rdpart/glfw/include)

link_directories(../3rdpart/glfw/lib/)


# 将源代码添加到此项目的可执行文件。
add_library (
	MMGL
	../3rdpart/glad/src/glad.c
	MMShader.cpp
	"MMProgram.cpp"
	"MMVAO.cpp" 
	"MMTexture.cpp")


# TODO: 如有需要，请添加测试并安装目标。
