#include "glm/gtc/matrix_transform.hpp"

#include "InputHandler.h"
#include "Game.h"
#include "Sorting.h"

Game* InputHandler::game_;

bool InputHandler::stallGameplayInputs_;

int getBiggestAbsolute(float x, float y, float z) {
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (z < 0) z = -z;
	if (x > y && x > z) return 0;
	if (y > x && y > z) return 1;
	if (z > x && z > y) return 2;
	return -1;
}

struct InputHandler::MouseInput {
	MouseInput(GLFWwindow* window, GLint button, GLint action, GLint mods)
		: window(window), button(button), action(action), mods(mods) {};

    GLFWwindow* window;
	GLint button;
	GLint action;
	GLint mods;
};

std::queue<InputHandler::MouseInput> InputHandler::stalledInputs_;

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
		MouseInput input = stalledInputs_.front();
		stalledInputs_.pop();
		MouseButtonCallBack(input.window, input.button, input.action, input.mods);
	}
}

#include <iostream>
void InputHandler::MouseButtonCallBack(GLFWwindow* window, GLint button, GLint action, GLint mods) {
	if (game_ == nullptr || button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS) return;
	if (stallGameplayInputs_) {
		MouseInput input(window, button, action, mods);
		stalledInputs_.push(input);
	}

	else {
		int direction = (mods && GLFW_MOD_SHIFT) ? -1 : 1;
		double xPos;
		double yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		xPos = 0; // xPos / (screenWidthC / 2) - 1.0;
		yPos = 0; // -yPos / (screenHeightC / 2) + 1.0; // screen coords gotta be invrted T_T

		std::cout << xPos << " " << yPos << " start" << std::endl;
		glm::mat4 screenToCoords = glm::inverse(game_->camera->GetCameraMatrix());
		glm::vec3 lineStart = glm::vec3(screenToCoords * glm::vec4(xPos, yPos, -2.0f, 1.0f));
		glm::vec3 lineEnd = glm::vec3(screenToCoords * glm::vec4(xPos, yPos, 0.0f, 1.0f));
		glm::vec3 delta = lineEnd - lineStart;
		std::vector<float> times(6);
		for (int i = 0; i < 6; i++) {
			int side = (i % 2 == 0) ? -1 : 1;
			float time = (side * 0.5f - lineStart[i / 2]) / delta[i / 2];
			// We use 2 as infinity here, if it doesn't get there we'll just set the time to 2.
			time = (0 <= time && time <= 1) ? time : 2.0f;
			times[i] = time;
		}
		for (size_t index : sort_indexes<float>(times)) {
			if (times[index] > 1.5f) return;
			size_t axis = index / 2;
			int side = (index % 2 == 0) ? -1 : 1;
			std::cout << index << " " << side << std::endl;
			glm::vec3 posAtTime = lineStart + times[index] * delta;
			std::cout << lineStart.x << " " << lineStart.y << " " << lineStart.z << std::endl;
			std::cout << posAtTime.x << " " << posAtTime.y << " " << posAtTime.z << std::endl;
			std::cout << delta.x << " " << delta.y << " " << delta.z << std::endl;
			bool withinBounds = true;
			for (int i = 0; i < 3; i++) {
				if (i != axis && (-0.5f > posAtTime[i] || 0.5f < posAtTime[i]))
					withinBounds = false;
			}
			if (withinBounds) {
				game_->RotateCube((Axis)axis, side, direction);
				return;
			}
		}
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
}
