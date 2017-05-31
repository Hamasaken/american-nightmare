#ifndef CAMERA_H
#define CAMERA_H

#include "../Accessories.h"
#include <SDL_mouse.h>

#define CAMERA_SPEED 0.09f
#define CAMERA_MOUSE_SPEED 0.07f

class Camera
{
public:
	Camera();
	Camera(SDL_Window* window, glm::vec2 screenSize);
	Camera(const Camera& other);
	~Camera();

	////////////////////////////////////////////////////////////
	// \brief Builds a view matrix with position and rotation
	// \note Needs to be built every frame!
	////////////////////////////////////////////////////////////
	void buildViewMatrix();

	////////////////////////////////////////////////////////////
	// \brief Set a new postition of the camera
	////////////////////////////////////////////////////////////
	void setPosition(glm::vec3 position);

	////////////////////////////////////////////////////////////
	// \brief Moving to position with a smooth function
	// \note Needs to be called multiple times to get effect
	////////////////////////////////////////////////////////////
	void smoothToPosition(glm::vec3 position);
	void smoothToPausePosition(glm::vec3 position);

	////////////////////////////////////////////////////////////
	// \brief Screenshake
	////////////////////////////////////////////////////////////
	void screenShake(float time, float power = 1.f);

	////////////////////////////////////////////////////////////
	// \brief Updates screenshake and moves to center
	////////////////////////////////////////////////////////////
	void Update(float deltaT);
	void UpdateUnlocked(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Gets the current view matrix
	// \note Only call this after you've called builtViewMatrix
	// \return The view matrix in 4x4
	////////////////////////////////////////////////////////////
	glm::mat4 getViewMatrix();

	////////////////////////////////////////////////////////////
	// \brief Gets the position of the camera
	// \return Returns a vector 3x1
	////////////////////////////////////////////////////////////
	glm::vec3 getPosition();

	////////////////////////////////////////////////////////////
	// \brief Sets the level position
	////////////////////////////////////////////////////////////
	void setFinishPosition(glm::vec3 position);
	void activateFinishAnimation();

	bool getUnlocked() const;

private:
	SDL_Window* window;
	glm::vec2 screenSize;
	glm::vec3 lookUp;
	glm::vec3 lookAt;
	glm::mat4 viewMatrix;	//< The camera's view matrix
	glm::vec3 position;		//< Position of the camera
	float pitch;
	float yaw;
	bool screenShakeActive;
	float screenShakeTime;
	float screenShakePower;

	float finishTimer;
	bool isFinishing;
	glm::vec3 finishPosition;

	bool unlock;
};

#endif // !CAMERA_H
