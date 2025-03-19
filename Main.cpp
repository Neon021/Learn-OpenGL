#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

#include "Shader.h"

//Callback function signatures
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int main() {

#pragma region Init and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#pragma endregion

#pragma region glfw window create
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#pragma endregion

#pragma region Load OpenGL funcitons
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialze GLAD" << std::endl;
		return -1;
	}
#pragma endregion

#pragma region build and compile vertex and fragment shaders
	Shader ourShader("vShader.vs", "fShader.fs");
#pragma endregion

#pragma region Set-up vertex buffer and attributes
	float vertices[] = {
		//positions			// colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f // top
	};

	//generate buffers and vertex array
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind first triangle VAO
	glBindVertexArray(VAO);
	//then bind and set vertex buffer(s) of first triangle
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//and then configure vertex attributes(s).
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#pragma endregion

#pragma region render loop
	int value = glfwWindowShouldClose(window);
	float triangleOffset = 0.0f;
	float oscillationSpeed = 0.5f;

	while (value == GLFW_FALSE) {
		triangleOffset = glfwGetTime() * oscillationSpeed;

		//input
		process_input(window);
		//color clear
		glClearColor(0.5f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		int horizontalOffsetLocation = glGetUniformLocation(ourShader.ID, "horizontalOffset");
		float xOffset = sin(triangleOffset);
		std::cout << "triangleOffset value:\n" << triangleOffset << std::endl;
		glUniform3f(horizontalOffsetLocation, xOffset, 0.0f, 0.0f);
		ourShader.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//check and call events swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		value = glfwWindowShouldClose(window);
	}
#pragma endregion

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	ourShader.deleteProgram();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}