#include "Camera.h"

Camera::Camera() 
{
	screenShakeActive = false;
}

Camera::Camera(const Camera& other) { }

Camera::~Camera() { }

void Camera::setPosition(glm::vec3 position) { this->position = position; }

void Camera::smoothToPosition(glm::vec3 position)
{
	this->position.x += (position.x - this->position.x) * CAMERA_SPEED;
	this->position.y += (position.y - this->position.y) * CAMERA_SPEED * 3;
}

void Camera::Update(float deltaT)
{
	// Screenshake
	if (screenShakeActive)
	{
		screenShakeTime -= deltaT;
		if (screenShakeTime < NULL) 
			screenShakeActive = false;

		position += randBetweenF(-0.1f * screenShakePower, 0.1f * screenShakePower);
	}

	// Updating viewMatrix
	buildViewMatrix();
}

void Camera::screenShake(float time, float power)
{
	screenShakeActive = true;
	screenShakeTime = time;
	screenShakePower = power;
}

glm::mat4 Camera::getViewMatrix() { return viewMatrix; }
glm::vec3 Camera::getPosition() { return position; }

void Camera::buildViewMatrix()
{
	glm::vec3 lookUp(0, 1, 0);
	glm::vec3 lookAt(0, 0, -1);
	glm::vec3 finalPos = position;
	finalPos.y += 2.50f;
	viewMatrix = glm::lookAt(finalPos, finalPos + lookAt, lookUp);
	//viewMatrix = glm::orthoLH(-20.f + position.x, 20.f + position.x, -20.f + position.y, 20.f + position.y, -8.f, 50.f);
}