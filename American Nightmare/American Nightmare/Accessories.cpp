#include "Accessories.h"
#include <iostream>

float getAngleFromTwoPoints(glm::vec3 p1, glm::vec3 p2)
{
	float dY = p1.y - p2.y;
	float dX = p1.x - p2.x;
	return atan2(dY, dX);
}

float getAngleFromTwoPoints(glm::vec3 p1, glm::vec3 p2)
int radianToDegree(float radian)
{
	int degree;
	return degree = (radian * 180) / PI;
}

float randBetweenF(float low, float high)
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

glm::vec2 fromScreenToNDC(glm::vec2 position, glm::vec2 screenSize, glm::vec2 screenPos)
{
	glm::vec2 tomas = glm::vec2(((position.x / screenSize.x) - screenPos.x / screenSize.x) * 2.f - 1.f,
		((position.y / screenSize.y) - screenPos.y / screenSize.y) * 2.f - 1.f);
		//std::cout << tomas.x << ", " << tomas.y << std::endl;
	return tomas; // temp
}

//glm::vec2 Angel(glm::vec2 position, glm::vec2 screenSize, glm::vec2 screenPos)
//{
//	glm::vec2 tomas = glm::vec2(((position.x / screenSize.x) - screenPos.x / screenSize.x) * 2.f - 1.f,
//		((position.y / screenSize.y) - screenPos.y / screenSize.y) * 2.f - 1.f);
//	std::cout << tomas.x << ", " << tomas.y << std::endl;
//	return glm::vec2(tomas.x * test, tomas.y * test); // temp
//}
	return glm::vec3(((position.x / screenSize.x) - screenPos.x / screenSize.x) * 2.f - 1.f,
						((position.y / screenSize.y) - screenPos.y / screenSize.y) * 2.f - 1.f, 1); // temp
}