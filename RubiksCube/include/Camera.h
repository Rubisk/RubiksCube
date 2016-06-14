#ifndef RUBIKS_CUBE_CAMERA_H_
#define RUBIKS_CUBE_CAMERA_H_

#include "glm/glm.hpp"

enum Direction {Up, Down, Left, Right, TiltLeft, TiltRight};

class Camera {
public:

	glm::mat4 GetCameraMatrix();

	void Rotate(Direction d, float angle);

private:
	glm::vec3 cameraPos = glm::vec3(1, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
};

#endif