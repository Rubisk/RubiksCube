#ifndef RUBIKS_CUBE_GAME_H_
#define RUBIKS_CUBE_GAME_H_

#include "Cube.h"
#include "Camera.h"
#include "InputHandler.h"

class Game {
public:
	Game();

	Camera camera;
	Cube cube;
};

#endif

