#ifndef RUBIKS_CUBE_CUBE_H_
#define RUBIKS_CUBE_CUBE_H_

#include <array>

#include "CubeOrientation.h"

class Cube {
public:
	void Rotate(Axis axis, int side, int direction);

	std::array<std::array<std::array<CubeOrientation, 3>, 3>, 3> blocks;
};

#endif