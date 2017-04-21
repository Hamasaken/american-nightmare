#include "Accessories.h"

float randBetweenF(float low, float high)
{
	return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

glm::vec3 fromScreenToWorld(glm::vec2 position)
{
	// temp
	return glm::vec3(position.x / (20.f / 1.11777), -position.y / (20.f / 1.12), 0); // temp
}

glm::vec3 fromScreenToWorld(glm::vec2 position, glm::vec2 screenSize, glm::mat4 world, glm::mat4 projection)
{
	// Do math



	return glm::vec3(0, 0, 0);
}