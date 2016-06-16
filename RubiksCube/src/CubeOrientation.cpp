#include <cassert>

#include "glm/gtx/rotate_vector.hpp"

#include "CubeOrientation.h"

// Sides are numbered 0-5
// 0 opposes 3, 1 opposes 4 and 2 opposes 5.

int Mod(int x, int y) {
	x = x % y;
	while (x < 0) x += y;
	return x % y;
}

void CubeOrientation::Rotate(Axis around, int angle) {
	for (int i = 0; i < angle / 90; i++) {
		if (around == Z) {
			_Rotate(X);
			_Rotate(Y);
			for (int j = 0; j < 3; j++) _Rotate(X); // rotate y inverse
		}
		else {
			_Rotate(around);
		}
	}
}

void CubeOrientation::_Rotate(Axis around) {
	if (around == Y) {
		// Top side won't change when turning around Y, since top = +Y.
		switch (topSide) {
		case 0:
			rightSide = rightSide + Mod(rightSide, 3);
			break;
		case 1:
			rightSide = rightSide + Mod((rightSide - 1), 3);
			break;
		case 2:
			rightSide = rightSide + Mod((rightSide + 1), 3);
			break;
		default: // topSide >= 3
			// Turn bottom to top, rotate the other way, rotate back.
			topSide -= 3;
			for (int j = 0; j < 3; j++) _Rotate(around);
			topSide += 3;
		}
	}
	else {

		// Right side won't change when turning around X, since right = +X.
		switch (rightSide) {
		case 0:
			topSide = topSide + Mod(topSide, 3);
			break;
		case 1:
			topSide = topSide + (Mod((topSide - 1), 3));
			break;
		case 2:
			topSide = topSide + (Mod((topSide + 1), 3));
			break;
		default: // topside >= 3
			// turn right side right, rotate the other way, rotate back.
			rightSide -= 3;
			for (int j = 0; j < 3; j++) _Rotate(around);
			rightSide += 3;
		}
	}
	topSide = Mod(topSide, 6);
	rightSide = Mod(rightSide, 6);
}

CubeOrientation::CubeOrientation() {
	topSide = 0;
	rightSide = 2;
}

std::queue<Rotation> CubeOrientation::GetRotations() {
	std::queue<Rotation> rotations;
	// Rotate x then y
	if (Mod(topSide, 3) != 2) {
		Rotation xRot;
		xRot.axis = X;
		xRot.angle = 0.0f;
		xRot.angle += (Mod(topSide, 3) == 1) ? 90.0f : 0.0f;
		xRot.angle += (topSide >= 3) ? 180.0f : 0.0f;
		rotations.push(xRot);

		Rotation yRot;
		yRot.axis = Y;
		if (Mod(rightSide, 3) == 2) {
			yRot.angle = (rightSide == 2) ? 0.0f : 180.0f;
		}
		else {
			yRot.angle = 90.0f;
			yRot.angle += (rightSide == 1 || rightSide == 3) ? 180.0f : 0.0f;
			yRot.angle += (3 == topSide || topSide == 4) ? 180.0f : 0.0f;
		}
		rotations.push(yRot);
	}
	// Rotate z then y
	else {
		Rotation zRot;
		zRot.axis = Z;
		zRot.angle = (topSide == 2) ? 270.0f : 90.0f;
		rotations.push(zRot);

		Rotation yRot;
		yRot.axis = Y;
		yRot.angle = 0.0f;
		yRot.angle += (topSide == 2 && Mod(rightSide, 3) == 0) ? 180.0f : 0.0f;
		yRot.angle += (Mod(rightSide, 3) == 0) ? 0.0f : 90.0f;
		yRot.angle += (rightSide >= 3) ? 180.0f : 0.0f;
		rotations.push(yRot);
	}
	return rotations;
}
