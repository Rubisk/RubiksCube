// Entry point of the program.

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Game.h"
#include "Renderer.h"
#include "Cube.h"

int main()
{
	std::shared_ptr<Game> game = std::make_shared<Game>();
	InputHandler::SetGame(game);

	Renderer renderer = Renderer(game);

	while (renderer.Draw());

    return 0;
}
