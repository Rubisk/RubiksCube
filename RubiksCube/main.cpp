// Entry point of the program.

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "Cube.h"

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw.";
		return -1;
	};

	// Setup some options and open the window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr); // Windowed

	glfwMakeContextCurrent(window);

	// Setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Create a cube and renderer
	Cube cube = Cube();
	Renderer renderer = Renderer(cube);

	// Main loop for drawing
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		renderer.Draw();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

    return 0;
}
