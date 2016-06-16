#include <iostream>

#include "InputHandler.h"
#include "Game.h"


std::weak_ptr<Game> InputHandler::game;

void InputHandler::SetGame(std::weak_ptr<Game> game) {
	InputHandler::game = game;
}

void InputHandler::KeyCallBack(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods) {

	if (game.expired()) return;

	std::shared_ptr<Game> g = game.lock();
	switch (key) {
	case GLFW_KEY_I:
		if (action == GLFW_PRESS)
			g->camera.StartRotate(Up);
		else if (action == GLFW_RELEASE)
			g->camera.StopRotate(Up);
		break;
	case GLFW_KEY_K:
		if (action == GLFW_PRESS)
			g->camera.StartRotate(Down);
		else if (action == GLFW_RELEASE)
			g->camera.StopRotate(Down);
		break;
	case GLFW_KEY_J:
		if (action == GLFW_PRESS)
			g->camera.StartRotate(Left);
		else if (action == GLFW_RELEASE)
			g->camera.StopRotate(Left);
		break;
	case GLFW_KEY_L:
		if (action == GLFW_PRESS)
			g->camera.StartRotate(Right);
		else if (action == GLFW_RELEASE)
			g->camera.StopRotate(Right);
		break;
	case GLFW_KEY_U:
		if (action == GLFW_PRESS)
			g->camera.StartRotate(TiltLeft);
		else if (action == GLFW_RELEASE)
			g->camera.StopRotate(TiltLeft);
		break;
	case GLFW_KEY_O:
		if (action == GLFW_PRESS)
			g->camera.StartRotate(TiltRight);
		else if (action == GLFW_RELEASE)
			g->camera.StopRotate(TiltRight);
		break;
	case GLFW_KEY_Q:
		if (action == GLFW_PRESS) {
			g->cube.blocks[0][0][0].Rotate(X, 90);
			// g->cube.blocks[0][1][1].Rotate(X, 90);
		}
		break;
	case GLFW_KEY_W:
		if (action == GLFW_PRESS) {
			g->cube.blocks[0][0][0].Rotate(Y, 90);
			// g->cube.blocks[0][1][1].Rotate(Y, 90);
		}
		break;
	case GLFW_KEY_E:
		if (action == GLFW_PRESS) {
			g->cube.blocks[0][0][0].Rotate(Z, 90);
			// g->cube.blocks[0][1][1].Rotate(Z, 90);
		}
		break;
	}
}
