#include "Camera.h"

Camera::Camera() { }

Camera::Camera(const Camera& other) { }

Camera::~Camera() { }

void Camera::setPosition(glm::vec3 position) { this->position = position; }
void Camera::setRotation(glm::vec3 rotation) { this->rotation = rotation; }

glm::mat4 Camera::getViewMatrix() { return viewMatrix; }
glm::vec3 Camera::getPosition() { return position; }
glm::vec3 Camera::getRotation() { return rotation; }

void Camera::buildViewMatrix()
{
	glm::vec3 lookUp(0, 1, 0);
	glm::vec3 lookAt(0, 0, -1);
	viewMatrix = glm::lookAt(position, position + lookAt, lookUp);
}