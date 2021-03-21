#include "MMPlayOpenGL.h"
#include "MMGL/MMGL.h"
#include <cstring>


#define STRINGIZE(x)  #x
#define SHADER(shader) "" STRINGIZE(shader)



MMOpenGLThread::MMOpenGLThread() {


}

MMOpenGLThread::~MMOpenGLThread() {
	while (freamQueue.Size() != 0) {
		MMAVFream* p = 0;
		freamQueue.Pop(&p);
		delete p;
		p = nullptr;
	}
}

int MMOpenGLThread::putFream(MMAVFream* f) {
	return freamQueue.Push(f);
}

void MMOpenGLThread::run() {
	// 初始化
	glfwInit();
	// 设置版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* windous = glfwCreateWindow(1280, 720, "OpenGl", NULL, NULL);
	glfwMakeContextCurrent(windous);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	char* vertexSource = SHADER(
		#version 330\n

		layout(location = 0) in vec3 pos;
		layout(location = 1) in vec3 aTexCoord;
		out vec2 texCoord;

	void main() {
		texCoord = vec2(aTexCoord.x, aTexCoord.y);
		gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	}
	);

	MMShader vertexShader = MMShader(vertexSource, MMShaderType::VERTEX);

	char* fragmentSource = SHADER(
	#version 330\n

	uniform sampler2D y_;
	uniform sampler2D u_;
	uniform sampler2D v_;


	in vec2 texCoord;

	out vec4 rgbaColor;

	void main() {
		vec2 t = vec2(texCoord.x, 1.0 - texCoord.y);

		vec3 yuv;
		vec3 rgb;

		yuv.x = texture(y_, t).r;
		// yuv.x = 0;
		yuv.y = texture(u_, t).r-0.5;
		 yuv.y = 0;
		yuv.z = texture(v_, t).r-0.5;
		 yuv.z = 0;

		rgb = mat3(1, 1, 1,
			0, -0.39465, 2.03211,
			1.13983, -0.58060, 0) * yuv;

		rgbaColor = vec4(rgb, 1.0);
	}

	);

	MMShader fragmentShader = MMShader(fragmentSource, MMShaderType::FRAGMENT);
	MMProgram mmprogram = MMProgram(vertexShader, fragmentShader);

	glUseProgram(mmprogram.programID);

	float vertices[] = {
		// 位置 
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};

	GLuint indices[] = { // 注意索引从0开始! 
		0,1,2,
		1,2,3
	};

	float texIndicess[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};



	MMVAO mmVAO = MMVAO();
	mmVAO.add3DVBO(vertices, sizeof(vertices), 0);
	mmVAO.addEBO(indices, sizeof(indices));
	mmVAO.add3DVBO(texIndicess, sizeof(texIndicess), 1);

	glBindVertexArray(mmVAO.vaoID);

	// 纹理
	GLuint textureY;
	GLuint textureU;
	GLuint textureV;


	glGenTextures(1, &textureY);
	glBindTexture(GL_TEXTURE_2D, textureY);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &textureU);
	glBindTexture(GL_TEXTURE_2D, textureU);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &textureV);
	glBindTexture(GL_TEXTURE_2D, textureV);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;

	GLint YtexttrueLocation = glGetUniformLocation(mmprogram.programID, "y_");
	GLint UtexttrueLocation = glGetUniformLocation(mmprogram.programID, "u_");
	GLint VtexttrueLocation = glGetUniformLocation(mmprogram.programID, "v_");
	



	MMAVFream* fream = 0;
	// 绘制
	while (stopFlag && !glfwWindowShouldClose(windous)) {

		if (freamQueue.Size() < 1) {
			continue;
		}

		//Clear
		//清除颜色设为黑色，把整个窗口清除为当前的清除颜色，glClear（）的唯一参数表示需要被清除的缓冲区。
		//glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);


		freamQueue.Pop(&fream);
		fream->setData(&width, &height, &nrChannels);
		// Y 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureY);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, fream->getYUVData(0));
		glUniform1i(YtexttrueLocation, 0);

		// U
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureU);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, fream->getYUVData(1));
		glUniform1i(UtexttrueLocation, 1);

		// V
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureV);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, fream->getYUVData(2));
		glUniform1i(VtexttrueLocation, 2);

		mmVAO.drawEBO(6);
		delete fream;
		fream = nullptr;
		//free(yuvData);
		glfwSwapBuffers(windous);
		glfwPollEvents();

	}

	glfwTerminate();
	return;
}