#include "MMGL.h"
#include <stdio.h>
#include <stdlib.h>

MMShader::MMShader(char * source, MMShaderType type) {
	
	if (type == MMShaderType::VERTEX) {
		mmShader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == MMShaderType::FRAGMENT) {
		mmShader = glCreateShader(GL_FRAGMENT_SHADER);
	}else {
		mmShader = glCreateShader(GL_VERTEX_SHADER);
	}
	

	glShaderSource(mmShader,1,&source,NULL);
	glCompileShader(mmShader);

	GLint logLen = 0;
	glGetShaderiv(mmShader,GL_INFO_LOG_LENGTH,&logLen);
	if (logLen > 0) {
		char* shaderLog = (char*)malloc(1024);
		glGetShaderInfoLog(mmShader,logLen,NULL, shaderLog);
		printf("Shader Error:\n");
		printf("%s\n", shaderLog);
		free(shaderLog);
	}
}

MMShader::~MMShader() {
	if (mmShader != 0) {
		glDeleteShader(mmShader);
		mmShader = 0;
	}
}