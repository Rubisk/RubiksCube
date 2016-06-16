#ifndef RUBIKS_CUBE_KEYHANDLER_H_
#define RUBIKS_CUBE_KEYHANDLER_H_

#include <memory>
#include <queue>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Game;

class InputHandler {

public:
	static void SetGame(Game* game);

	static void StallGameplayInputs(bool setting);

	static void KeyCallBack(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
private:
	struct Input;

	static bool stallGameplayInputs_;

	static void TryProcessStalledInputs_();
	
	static std::queue<Input> stalledInputs_;

	static Game* game_;
};

#endif