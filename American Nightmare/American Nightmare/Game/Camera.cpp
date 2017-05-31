#include "Camera.h"

Camera::Camera() 
{
	screenShakeActive = false;
	isFinishing = false;
	finishTimer = 0.f;
	unlock = false;
	lookUp = glm::vec3(0, 1, 0);
	lookAt = glm::vec3(0, 0, -1);
}

Camera::Camera(const Camera& other) { }

Camera::~Camera() { }

void Camera::setPosition(glm::vec3 position) { this->position = position; }

void Camera::smoothToPosition(glm::vec3 position)
{
	if (!isFinishing && !unlock)
	{
		this->position.x += (position.x - this->position.x) * CAMERA_SPEED;
		this->position.y += (position.y - this->position.y) * CAMERA_SPEED * 3;
		this->position.z += (16.f - this->position.z) * CAMERA_SPEED;
		this->lookAt.x += (0 - this->lookAt.x) * CAMERA_SPEED;
		this->lookAt.y += (0 - this->lookAt.y) * CAMERA_SPEED * 3;
	}
}

void Camera::smoothToPausePosition(glm::vec3 position)
{
	this->position.x += ((position.x - 5.05f) - this->position.x) * CAMERA_SPEED;
	this->position.y += ((position.y) - this->position.y) * CAMERA_SPEED * 3;
	this->position.z += (10.f - this->position.z) * CAMERA_SPEED;
	this->lookAt.x += (0.5f - this->lookAt.x) * CAMERA_SPEED;
	this->lookAt.y += (-0.25f - this->lookAt.y) * CAMERA_SPEED * 3;
}

void Camera::Update(float deltaT)
{
	// Is Finishing animation
	if (isFinishing)
	{
		position += (finishPosition - position) * 0.01f;
		lookAt += (glm::vec3(1, 0, 0) - lookAt) * 0.1f;

		finishTimer -= deltaT;
		if (finishTimer < 0.f)
		{
			isFinishing = false;
			finishPosition = glm::vec3(0.f);
			lookAt = glm::vec3(0, 0, -1);
		}
	}

	// Screenshake
	if (screenShakeActive)
	{
		screenShakeTime -= deltaT;
		if (screenShakeTime < NULL) 
			screenShakeActive = false;

		position += randBetweenF(-0.1f * screenShakePower, 0.1f * screenShakePower);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
	{
		unlock = !unlock;
	}


	if (unlock)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			lookAt.y += 0.01f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			lookAt.y -= 0.01f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			lookAt.x -= 0.05f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			lookAt.x += 0.05f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			position.z -= 0.25f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			position.z += 0.25f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			position.x -= 0.25f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			position.x += 0.25f;
		}
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

void Camera::setFinishPosition(glm::vec3 position)
{
	this->finishPosition = position;
}

void Camera::activateFinishAnimation()
{
	isFinishing = true;
	finishTimer = 2000.f;
}

void Camera::buildViewMatrix()
{
	glm::vec3 finalPos = position;
	finalPos.y += 2.50f;
	viewMatrix = glm::lookAt(finalPos, finalPos + lookAt, lookUp);
	//viewMatrix = glm::orthoLH(-20.f + position.x, 20.f + position.x, -20.f + position.y, 20.f + position.y, -8.f, 50.f);
}

bool Camera::getUnlocked() const { return unlock; }