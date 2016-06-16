#include "Camera.h"
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera() {
	for (int i = 0; i < NumberOfDirections; i++) {
		turnDirections[i] = false;
	}
}

glm::mat4 Camera::GetCameraMatrix() {
	Update();
	return glm::lookAt(cameraPos, glm::vec3(0, 0, 0), up);
};


void Camera::StartRotate(Direction d) {
	Update();
	turnDirections[d] = true;
};

void Camera::StopRotate(Direction d) {
	Update();
	turnDirections[d] = false;
};

void Camera::Update() {
	std::time_t newTime = clock();

	float totalDirections = 0;
	for (bool b : turnDirections) {
		if (b) ++totalDirections;
	};

	time_t timePassed = newTime - lastUpdated;
	lastUpdated = newTime;
	if (totalDirections == 0) return;

	float angle = ((float) timePassed) * rotationSpeed / sqrt(totalDirections);

	float c;
	glm::vec3 axis;
	for (int d = 0; d < NumberOfDirections; d++) {
		if (!turnDirections[d]) continue;
		switch (d) {
		case Up:
		case Down:
			c = (d == Down) ? 1.0f : -1.0f;  // flip or not
			axis = c * glm::cross(cameraPos, up);
			cameraPos = glm::rotate(cameraPos, angle, axis);
			up = glm::rotate(up, angle, axis);
			break;
		case Left:
		case Right:
			c = (d == Left) ? 1.0f : -1.0f;  // flip or not
			axis = c * up;
			cameraPos = glm::rotate(cameraPos, angle, axis);
			break;
		case TiltLeft:
		case TiltRight:
			c = (d == TiltLeft) ? 1.0f : -1.0f;  // flip or not
			axis = c * cameraPos;
			up = glm::rotate(up, angle, axis);
			break;
		}
	}
};