#include "MMPlayOpenGL.h"


#include "3rdpart/stbimage/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

#define STRINGIZE(x)  #x
#define SHADER(shader) "" STRINGIZE(shader)

int main()
{
	
	// 初始化
	glfwInit();
	// 设置版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 设置模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* windous = glfwCreateWindow(1280, 720, "OpenGl", NULL, NULL);

	// 绑定线程 OpenGL不建议多线程
	glfwMakeContextCurrent(windous);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);



	// 着色器

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

		uniform sampler2D t;

		in vec2 texCoord;

		out vec4 rgbaColor;

		void main(){
	
			// rgbaColor = vec4(1.0, 0, 0, 1.0);
			rgbaColor = texture(t, texCoord);

		}

	);

	MMShader fragmentShader = MMShader(fragmentSource, MMShaderType::FRAGMENT);
	MMProgram mmprogram = MMProgram(vertexShader, fragmentShader);

	glUseProgram(mmprogram.programID);

	// 初始化完成


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
	mmVAO.add3DVBO(texIndicess,sizeof(texIndicess),1);
	glBindVertexArray(mmVAO.vaoID);


	// 纹理
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("C://Users/Time/Desktop/wall.jpg", &width, &height, &nrChannels, 0);
	
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


	GLint texttrueLocation = glGetUniformLocation(mmprogram.programID, "t");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texttrueLocation, 0);


	// 绘制
	while (!glfwWindowShouldClose(windous)) {
		
		glClear(GL_COLOR_BUFFER_BIT);
	
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		mmVAO.drawEBO(6);
		

		glfwSwapBuffers(windous);
		glfwPollEvents();

	}

	glfwTerminate();
	stbi_image_free(data);
	return 0;
}

