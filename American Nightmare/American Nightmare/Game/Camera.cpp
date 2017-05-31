#include "Camera.h"

Camera::Camera()
{
	window = nullptr;
	screenSize = glm::vec2(0.f);
	screenShakeActive = false;
	isFinishing = false;
	finishTimer = 0.f;
	unlock = false;
	pitch = 0.f;
	yaw = -90.f;
	lookUp = glm::vec3(0, 1, 0);
	lookAt = glm::vec3(0, 0, -1);
}

Camera::Camera(SDL_Window* window, glm::vec2 screenSize)
{
	this->window = window;
	this->screenSize = screenSize;
	screenShakeActive = false;
	isFinishing = false;
	finishTimer = 0.f;
	unlock = false;
	pitch = 0.f;
	yaw = -90.f;
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
		this->lookAt.z += (-1.f - this->lookAt.z) * CAMERA_SPEED;
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
		UpdateUnlocked(deltaT);
	}
	

	// Updating viewMatrix
	buildViewMatrix();
}

void Camera::UpdateUnlocked(GLint deltaT)
{
	int tmpX, tmpY;
	SDL_GetMouseState(&tmpX, &tmpY);

	yaw += CAMERA_MOUSE_SPEED * (tmpX - (screenSize.x * 0.5f));
	pitch += CAMERA_MOUSE_SPEED * ((screenSize.y * 0.5f) - tmpY);

	// Lock camera
	if (pitch > 89)
		pitch = 89;
	if (pitch < -89)
		pitch = -89;
	if (yaw < 0.f)
		yaw += 360.f;
	if (yaw > 360.f)
		yaw -= 360.f;

	// pitch and yaw
	glm::vec3 direction;
	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	lookAt = glm::normalize(direction);

	// reset mouse to center
	SDL_WarpMouseInWindow(window, screenSize.x * 0.5f, screenSize.y * 0.5f);

	// keyboard movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		position += 2.f * CAMERA_MOUSE_SPEED * lookAt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position -= 2.f * CAMERA_MOUSE_SPEED * lookAt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		position -= glm::normalize(glm::cross(lookAt, lookUp)) * CAMERA_MOUSE_SPEED * 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position += glm::normalize(glm::cross(lookAt, lookUp)) * CAMERA_MOUSE_SPEED * 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		position += lookUp * CAMERA_MOUSE_SPEED * 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		position += -lookUp * CAMERA_MOUSE_SPEED * 2.f;
	}
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