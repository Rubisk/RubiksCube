#ifndef RUBISK_CUBE_BLOCK_H_
#define RUBISK_CUBE_BLOCK_H_

enum Axis {
	X,
	Y,
	Z,
};

class Block { 
public:
	int GetRotation(Axis around);

	void Rotate(Axis around, int degrees);

private:
	int XRotation;
	int YRotation;
};

#endif