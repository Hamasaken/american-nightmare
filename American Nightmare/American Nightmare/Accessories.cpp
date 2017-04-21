#include "Accessories.h"

float randBetweenF(float low, float high)
{
	return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

glm::vec3 fromScreenToWorld(glm::vec2 position)
{
	return glm::vec3(position.x / (20.f / 1.11777), -position.y / (20.f / 1.12), 0); // temp
}