#include "Renderer.h"
#include "Shader.h"

#include "GL/glew.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLfloat cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.51f, -0.45f, -0.45f,
	-0.51f, -0.45f,  0.45f,
	-0.51f,  0.45f, -0.45f,
	-0.51f,  0.45f,  0.45f,

	 0.51f, -0.45f, -0.45f,
	 0.51f, -0.45f,  0.45f,
	 0.51f,  0.45f, -0.45f,
	 0.51f,  0.45f,  0.45f,

	-0.45f, -0.51f, -0.45f,
	-0.45f, -0.51f,  0.45f,
	 0.45f, -0.51f, -0.45f,
	 0.45f, -0.51f,  0.45f,

	-0.45f,  0.51f, -0.45f,
	-0.45f,  0.51f,  0.45f,
	 0.45f,  0.51f, -0.45f,
	 0.45f,  0.51f,  0.45f,

	-0.45f, -0.45f, -0.51f,
	-0.45f,  0.45f, -0.51f,
	 0.45f, -0.45f, -0.51f,
	 0.45f,  0.45f, -0.51f,

	-0.45f, -0.45f,  0.51f,
    -0.45f,  0.45f,  0.51f,
	 0.45f, -0.45f,  0.51f,
	 0.45f,  0.45f,  0.51f,
};

GLuint cubeIndices[] = {
	// Outer Cube
	0, 1, 3,
	0, 2, 3,
	0, 1, 5,
	0, 4, 5,
	0, 2, 6,
	0, 4, 6,
	7, 1, 3,
	7, 1, 5,
	7, 2, 3,
	7, 2, 6,
	7, 4, 5,
	7, 4, 6,

	// Face 1
	8, 9, 11,
	8, 10, 11,

	// Face 2
	12, 13, 15,
	12, 14, 15,

	// Face 3
	16, 17, 19,
	16, 18, 19,

	// Face 4
	20, 21, 23,
	20, 22, 23,

	// Face 5
	24, 25, 27,
	24, 26, 27,

	// Face 6
	28, 29, 31,
	28, 30, 31,
};

GLfloat colorVertices[] = {
	// BLACK INNER CUBE
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,

	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.7f, 0.0f,
	0.0f, 0.7f, 0.0f,
	0.0f, 0.7f, 0.0f,
	0.0f, 0.7f, 0.0f,
};

Renderer::Renderer(Cube c) {
	cube = c;

	shaderProgram = CreateShaderProgram("shaders/shader.vs", "shaders/shader.frag");

	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);
	glGenBuffers(1, &colorBuffer);
	glGenBuffers(1, &colorIndexBuffer);

	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorVertices), colorVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);

	glBindVertexArray(0);
};

void Renderer::Draw(GLFWwindow* window) {

	// TODO move this out of draw loop
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) camera.Rotate(Up, 0.01f);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) camera.Rotate(Down, 0.01f);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) camera.Rotate(Left, 0.01f);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) camera.Rotate(Right, 0.01f);
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) camera.Rotate(TiltLeft, 0.01f);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) camera.Rotate(TiltRight, 0.01f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8f, 0.8f, 0.8f, 1);

	glUseProgram(shaderProgram);
	glBindVertexArray(vertexArray);

	GLuint modelUni = glGetUniformLocation(shaderProgram, "model");
	GLuint cameraUni = glGetUniformLocation(shaderProgram, "camera");
	GLuint projectionUni = glGetUniformLocation(shaderProgram, "projection");

	glm::mat4 cameraMatrix = camera.GetCameraMatrix();
	glUniformMatrix4fv(cameraUni, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	glm::mat4 projection = glm::perspective(glm::radians(55.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionUni, 1, GL_FALSE, glm::value_ptr(projection));

	const float size = 0.150f;

	for (int ix = 0; ix < 3; ix++) {
		for (int iy = 0; iy < 3; iy++) {
			for (int iz = 0; iz < 3; iz++) {
				glm::mat4 model;
				model = glm::translate(model, glm::vec3(size * (ix - 1), size * (iy - 1), size * (iz - 1)));
				model = glm::scale(model, glm::vec3(size, size, size));
				glUniformMatrix4fv(modelUni, 1, GL_FALSE, glm::value_ptr(model));

				glDrawElements(GL_TRIANGLES, sizeof(cubeIndices), GL_UNSIGNED_INT, 0);
			}
		}
	}
	glBindVertexArray(0);
};

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &elementBuffer);
	glDeleteBuffers(1, &colorBuffer);
}
