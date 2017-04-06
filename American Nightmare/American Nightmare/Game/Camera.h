#ifndef CAMERA_H
#define CAMERA_H

#include "Accessories.h"

class Camera
{
public:
	Camera();
	Camera(const Camera& other);
	~Camera();

	void buildViewMatrix();
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);

	glm::mat4 getViewMatrix();
	glm::vec3 getPosition();
	glm::vec3 getRotation();

private:
	glm::mat4 viewMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
};

#endif // !CAMERA_H
