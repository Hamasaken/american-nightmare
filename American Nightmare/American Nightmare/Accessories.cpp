#include "Accessories.h"

float getAngleFromTwoPoints(glm::vec3 p1, glm::vec3 p2)
{
	float dY = p1.y - p2.y;
	float dX = p1.x - p2.x;
	return atan2(dY, dX);
}

float randBetweenF(float low, float high)
{
	return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

glm::vec3 fromScreenToNDC(glm::vec2 position, glm::vec2 screenSize, glm::vec2 screenPos)
{
	return glm::vec3(((position.x / screenSize.x) - screenPos.x / screenSize.x) * 2.f - 1.f,
						((position.y / screenSize.y) - screenPos.y / screenSize.y) * 2.f - 1.f, 1); // temp
}