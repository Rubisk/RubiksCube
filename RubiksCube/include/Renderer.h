#ifndef RUBIKS_CUBE_RENDERER_H_
#define RUBIKS_CUBE_RENDERER_H_

#include "Cube.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Camera.h"


class Renderer
{
public:
	Renderer(Cube cube);

	Renderer::~Renderer();
	
	void Draw(GLFWwindow* window);
private:
	GLuint shaderProgram;

	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint colorBuffer;
	GLuint colorIndexBuffer;

	Cube cube;

	Camera camera;

	GLuint vertexArray;
};

#endif