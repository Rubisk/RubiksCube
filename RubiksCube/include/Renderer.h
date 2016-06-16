#ifndef RUBIKS_CUBE_RENDERER_H_
#define RUBIKS_CUBE_RENDERER_H_

#include <ctime>
#include <memory>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Cube.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer(std::weak_ptr<Cube> cube, std::weak_ptr<Camera>);

	void StartTurnAnimation(Axis axis, int side, int direction);

	bool IsAnimating();

	void Draw();

	~Renderer();
private:
	void LoadCubeVertices();

	glm::mat4 _GetAnimateBlockMatrix(int x, int y, int z);

	std::weak_ptr<Cube> cube_;
	std::weak_ptr<Camera> camera_;

	GLuint shaderProgram;
	GLuint vertexArray;

	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint colorBuffer;

	std::clock_t timeSinceLastFrame;
	std::clock_t animationStartTime;
	Axis animationAxis;
	int animationSide;
	int animationDirection;
	bool isAnimating_;
	bool shouldStopAnimating_;
};

#endif