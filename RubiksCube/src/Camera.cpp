#include "Camera.h"
#include "glm/gtx/rotate_vector.hpp"


glm::mat4 Camera::GetCameraMatrix() {
	return glm::lookAt(cameraPos, glm::vec3(0, 0, 0), up);
};


void Camera::Rotate(Direction d, float angle) {
	float c;
	glm::vec3 axis;
	switch (d) {
	case Up:
	case Down:
		c = (d == Down) ? 1 : -1;  // flip or not
		axis = c * glm::cross(cameraPos, up);
		cameraPos = glm::rotate(cameraPos, angle, axis);
		up = glm::rotate(up, angle, axis);
		break;
	case Left:
	case Right:
		c = (d == Left) ? 1 : -1;  // flip or not
		axis = c * up;
		cameraPos = glm::rotate(cameraPos, angle, axis);
		break;
	case TiltLeft:
	case TiltRight:
		c = (d == TiltLeft) ? 1 : -1;  // flip or not
		axis = c * cameraPos;
		up = glm::rotate(up, angle, axis);
		break;
	}
}