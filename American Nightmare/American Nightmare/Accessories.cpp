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

glm::vec3 fromScreenToWorld(glm::vec2 position, glm::vec2 screenSize, glm::mat4 view, glm::mat4 projection)
{
	glm::mat4 result = view * projection;
	glm::mat4 inversed = glm::inverse(result);

	glm::vec4 in; // between -1:1 x/y, z is depth -1:1, w is 1
	in.x = ((2.0f * ((position.x) / (screenSize.x))) - 1.0f) * -1.f; // flipping
	in.y = (1.0f - (2.0f * ((position.y) / (screenSize.y)))); // flipping also
	in.z = 1;
	in.w = 1;

	glm::vec4 finalResult = in * inversed;
	finalResult.w = 1.0f / finalResult.w;
	finalResult.x *= finalResult.w;
	finalResult.y *= finalResult.w;
	finalResult.z *= finalResult.w;

	return finalResult;
}