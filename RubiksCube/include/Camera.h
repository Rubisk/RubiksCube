#ifndef RUBIKS_CUBE_CAMERA_H_
#define RUBIKS_CUBE_CAMERA_H_

#include <ctime>

#include "glm/glm.hpp"

enum Direction { Up, Down, Left, Right, TiltLeft, TiltRight, NumberOfDirections };

class Camera {
public:
	Camera();

	glm::mat4 GetCameraMatrix();

	void StartRotate(Direction d);

	void StopRotate(Direction d);
private:
	void Update();

	bool turnDirections[NumberOfDirections];

	float rotationSpeed = 0.003f;
	std::time_t lastUpdated;
	glm::vec3 cameraPos = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);
};

#endif