#ifndef RUBISK_CUBE_CUBE_ORIENTATION_H_
#define RUBISK_CUBE_CUBE_ORIENTATION_H_

#include <queue>

#include "glm\glm.hpp"

enum Axis {
	X,
	Y,
	Z,
};

struct Rotation {
	float angle;
	Axis axis;
};

class CubeOrientation { 
public:
	CubeOrientation();
	// Returns the minimal amount of rotations needed to get an object
	// in this orientation.
	std::queue<Rotation> GetRotations();

	void Rotate(Axis around, int times);

private:
	void _Rotate(Axis around);

	int topSide;
	int rightSide;
};

#endif