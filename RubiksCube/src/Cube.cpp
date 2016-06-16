#include <iostream>

#include "Cube.h"

void Cube::Rotate(Axis axis, int side, int direction) {
	assert(side == 1 || side == -1);
	assert(direction == 1 || direction == -1);

	std::array<std::array<CubeOrientation, 3>, 3> _blocks;
	switch (axis) {
	case X:
		for (int y = -1; y < 2; y++) {
			for (int z = -1; z < 2; z++) {
				_blocks[-direction * z + 1][direction * y + 1] = blocks[side + 1][y + 1][z + 1];
				int times = (direction == 1) ? 1 : 3;
				_blocks[-direction * z + 1][direction * y + 1].Rotate(axis, times);
			}
		}
		blocks[side + 1] = _blocks;
		break;
	case Y:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				_blocks[direction * z + 1][-direction * x + 1] = blocks[x + 1][side + 1][z + 1];
				int times = (direction == 1) ? 1 : 3;
				_blocks[direction * z + 1][-direction * x + 1].Rotate(axis, times);
			}
		}
		for (int x = 0; x < 3; x++) {
			blocks[x][side + 1] = _blocks[x];
		}
		break;
	case Z:
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				_blocks[-direction * y + 1][direction * x + 1] = blocks[x + 1][y + 1][side + 1];
				int times = (direction == 1) ? 3 : 1;
				_blocks[-direction * y + 1][direction * x + 1].Rotate(axis, times);
			}
		}
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				blocks[x][y][side + 1] = _blocks[x][y];
			}
		}

	}
}