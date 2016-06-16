#ifndef RUBIKS_CUBE_KEYHANDLER_H_
#define RUBIKS_CUBE_KEYHANDLER_H_

#include <memory>

#include "GLFW/glfw3.h"

class Game;

class InputHandler {

public:
	static void SetGame(std::weak_ptr<Game> game);

	static void KeyCallBack(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
private:
	static std::weak_ptr<Game> game;
};

#endif