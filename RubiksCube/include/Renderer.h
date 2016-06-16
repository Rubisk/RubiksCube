#ifndef RUBIKS_CUBE_RENDERER_H_
#define RUBIKS_CUBE_RENDERER_H_

#include <ctime>
#include <memory>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Cube.h"
#include "Camera.h"
#include "Game.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<Game> game);

	Renderer::~Renderer();
	
	bool Draw();
private:
	std::shared_ptr<Game> game;

	void LoadCubeVertices();

	GLFWwindow* window;

	GLuint shaderProgram;
	GLuint vertexArray;

	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint colorBuffer;

	Cube cube;

	std::clock_t timeSinceLastFrame;
};

#endif