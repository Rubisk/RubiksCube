#include <memory>
#include <iostream>
#include <thread>
#include "Game.h"


Game::Game() {
	cube = std::make_shared<Cube>();
	camera = std::make_shared<Camera>();
}

void Game::Start() {
	if (!glfwInit())
		std::cout << "Failed to initialize glfw.";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "Rubiks Cube", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, (GLFWkeyfun) InputHandler::KeyCallBack);
	InputHandler::SetGame(this);

	renderer = std::make_shared<Renderer>(cube, camera);
	while (Tick_());
	Stop();
}

void Game::Stop() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Game::Tick_() {
	renderer->Draw();
	glfwSwapBuffers(window);
	glfwPollEvents();
	return !glfwWindowShouldClose(window);
}


void Game::RotateCube(Axis axis, int side, int direction) {
	renderer->StartTurnAnimation(axis, side, direction);
	InputHandler::StallGameplayInputs(true);
	while (renderer->IsAnimating()) Tick_();
	cube->Rotate(axis, side, direction);
	InputHandler::StallGameplayInputs(false);
}
