#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

enum MMShaderType
{
	VERTEX = 0,
	FRAGMENT = 1
};

class MMShader {
public :
	MMShader(char* source, MMShaderType type);
	~MMShader();

public:
	GLuint mmShader = 0;
}; 

class MMProgram {
public:
	MMProgram(MMShader& vertexShader, MMShader& fragmentShader);
	~MMProgram();

public:
	GLuint programID = 0;
};

class MMVAO {
public:
	MMVAO();
	~MMVAO();

	int add3DVBO(float* verticesVector, int buffsize, int layout);
	int addEBO(unsigned int * indices, int buffsize);
	void drawEBO(int pointCount);

public:
	GLuint vaoID = 0;
	GLuint eboID = 0;
	std::vector<GLuint> vboList;
};

class MMTexture {
public:
	MMTexture();
	~MMTexture();
public:
	GLuint textureID = 0;
	int width, height, nrChannels;
};