#include "InputHandler.h"
#include "Game.h"


Game* InputHandler::game_;

bool InputHandler::stallGameplayInputs_;

struct InputHandler::Input {
    GLFWwindow* window;
	GLint key;
	GLint scancode;
	GLint action;
	GLint mods;
};

std::queue<InputHandler::Input> InputHandler::stalledInputs_;

void InputHandler::SetGame(Game* game) {
	InputHandler::game_ = game;
}

void InputHandler::StallGameplayInputs(bool setting) {
	// if (stallGameplayInputs_ == setting) return;
	stallGameplayInputs_ = setting;
	TryProcessStalledInputs_();
}

void InputHandler::TryProcessStalledInputs_() {
	while (!stalledInputs_.empty() && !stallGameplayInputs_) {
		Input input = stalledInputs_.front();
		stalledInputs_.pop();
		KeyCallBack(input.window, input.key, input.scancode, input.action, input.mods);
	}
}

void InputHandler::KeyCallBack(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods) {
	if (game_ == nullptr) return;

	switch (key) {
	case GLFW_KEY_I:
		if (action == GLFW_PRESS)
			game_->camera->StartRotate(Up);
		else if (action == GLFW_RELEASE)
			game_->camera->StopRotate(Up);
		return;
	case GLFW_KEY_K:
		if (action == GLFW_PRESS)
			game_->camera->StartRotate(Down);
		else if (action == GLFW_RELEASE)
			game_->camera->StopRotate(Down);
		return;
	case GLFW_KEY_J:
		if (action == GLFW_PRESS)
			game_->camera->StartRotate(Left);
		else if (action == GLFW_RELEASE)
			game_->camera->StopRotate(Left);
		return;
	case GLFW_KEY_L:
		if (action == GLFW_PRESS)
			game_->camera->StartRotate(Right);
		else if (action == GLFW_RELEASE)
			game_->camera->StopRotate(Right);
		return;
	case GLFW_KEY_U:
		if (action == GLFW_PRESS)
			game_->camera->StartRotate(TiltLeft);
		else if (action == GLFW_RELEASE)
			game_->camera->StopRotate(TiltLeft);
		return;
	case GLFW_KEY_O:
		if (action == GLFW_PRESS)
			game_->camera->StartRotate(TiltRight);
		else if (action == GLFW_RELEASE)
			game_->camera->StopRotate(TiltRight);
		return;
	}
	if (stallGameplayInputs_) {
		Input input;
		input.window = window;
		input.key = key;
		input.action = action;
		input.scancode = scancode;
		input.mods = mods;
		stalledInputs_.push(input);
	}
	else {
		switch (key) {
		case GLFW_KEY_Q:
			if (action == GLFW_PRESS) {
				int side = (mods && GLFW_MOD_SHIFT) ? -1 : 1;
				game_->RotateCube(X, side, 1);
			}
			break;
		case GLFW_KEY_W:
			if (action == GLFW_PRESS) {
				int side = (mods && GLFW_MOD_SHIFT) ? -1 : 1;
				game_->RotateCube(Y, side, 1);
			}
			break;
		case GLFW_KEY_E:
			if (action == GLFW_PRESS) {
				int side = (mods && GLFW_MOD_SHIFT) ? -1 : 1;
				game_->RotateCube(Z, side, 1);
			}
			break;
		}
	}
}
