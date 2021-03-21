#include "MMGL.h"
#include <stdio.h>
#include <stdlib.h>

MMProgram::MMProgram(MMShader &vertexShader, MMShader &fragmentShader) {
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader.mmShader);
	glAttachShader(programID, fragmentShader.mmShader);
	glLinkProgram(programID);
	GLint logLen = 0;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLen);
	if(logLen > 0){
		char* programLog = (char*)malloc(1024);
		glGetProgramInfoLog(programID, logLen, NULL, programLog);
		printf("Program Error:\n");
		printf("%s\n", programLog);
		free(programLog);
	}
}

MMProgram::~MMProgram() {
	if (programID != 0) {
		glDeleteProgram(programID);
		programID = 0;
	}
}
