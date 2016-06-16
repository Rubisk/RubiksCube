#ifndef RUBIKS_CUBE_CUBE_H_
#define RUBIKS_CUBE_CUBE_H_

#include "CubeOrientation.h"

class Cube {
public:
	CubeOrientation blocks[3][3][3];
};

#endif