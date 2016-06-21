#ifndef RUBIKS_CUBE_GAME_H_
#define RUBIKS_CUBE_GAME_H_

#include "Cube.h"
#include "Camera.h"
#include "InputHandler.h"
#include "Renderer.h"

const int screenWidthC = 800;
const int screenHeightC = 600;


class Game {
public:
	Game();

	void Start();

	void Stop();

	void RotateCube(Axis axis, int side, int direction);
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Cube> cube;

protected:
	GLFWwindow* window;

	bool Tick_();
};

#endif

