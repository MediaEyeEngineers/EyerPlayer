#include "MMGL.h"

MMVAO::MMVAO() {
	glGenVertexArrays(1, &vaoID);
}

MMVAO::~MMVAO() {
	for(auto &e : vboList){
		glDeleteBuffers(1, &e);
		e = 0;
	}
	vboList.clear();

	if (eboID != 0) {
		glDeleteBuffers(1, &eboID);
		eboID = 0;
	}

	if(vaoID != 0 ){
		glDeleteVertexArrays(1, &vaoID);
		vaoID = 0;
	}
}

int MMVAO::add3DVBO(float *verticesVector,int buffsize, int layout) {
	glBindVertexArray(vaoID);

	GLuint VBO = 0;

	glGenBuffers(1, &VBO);
	vboList.push_back(VBO);
	// °ó¶¨
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, buffsize, verticesVector, GL_STATIC_DRAW);

	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(layout);
	
	
	// ½â°ó
	glBindVertexArray(0);
	
	return 0;
}

int MMVAO::addEBO(unsigned int* indices, int buffsize ) {


	glBindVertexArray(vaoID);

	glGenBuffers(1, &eboID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffsize, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	return 0;
}

void MMVAO::drawEBO(int pointCount) {
	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, pointCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

