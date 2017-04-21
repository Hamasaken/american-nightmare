#include "Frustum.h"

Frustum::Frustum() { }

Frustum::Frustum(const Frustum & other) { }

Frustum::~Frustum() { }

void Frustum::Start(float screenDepth, glm::mat4 viewMatrix, glm::mat4 orthoMatrix)
{
	// Make planes
	glm::mat4 frustum = viewMatrix * orthoMatrix;

}

bool Frustum::IsPointInside(glm::vec3 position)
{
	return false;
}

bool Frustum::IsCubeInside(glm::vec3 center, float side)
{
	return false;
}

bool Frustum::IsSphereInside(glm::vec3 center, float radius)
{
	return false;
}

bool Frustum::IsRectangleInside(glm::vec3 center, glm::vec3 dimensions)
{
	return false;
}
