#include "Accessories.h"

float randBetweenF(float low, float high)
{
	return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

glm::vec3 fromScreenToWorld(glm::vec2 position, glm::vec2 screenSize, glm::vec2 screenPos)
{
	return glm::vec3(((position.x / screenSize.x) - screenPos.x / screenSize.x) * 2.f - 1.f,
						((position.y / screenSize.y) - screenPos.y / screenSize.y) * 2.f - 1.f, 1); // temp
}