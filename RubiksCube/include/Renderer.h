#ifndef RUBIKS_CUBE_RENDERER_H_
#define RUBIKS_CUBE_RENDERER_H_

#include "Cube.h"
#include "GL/glew.h"


class Renderer
{
public:
	Renderer(Cube cube);

	Renderer::~Renderer();
	
	void Draw();
private:
	GLuint shaderProgram;

	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint colorBuffer;
	GLuint colorIndexBuffer;

	Cube cube;

	GLuint vertexArray;
};

#endif