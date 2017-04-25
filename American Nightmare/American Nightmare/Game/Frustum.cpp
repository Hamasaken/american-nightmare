#include "Frustum.h"

Frustum::Frustum() { }

Frustum::Frustum(const Frustum & other) { }

Frustum::~Frustum() { }

void Frustum::Start(float screenDepth, glm::mat4 viewMatrix, glm::mat4 orthoMatrix)
{
	glm::mat4 frustum = viewMatrix * orthoMatrix;

	Plane left;
	left.a = frustum[0][0] + frustum[3][0];
	left.b = frustum[0][1] + frustum[3][1];
	left.c = frustum[0][2] + frustum[3][2];
	left.d = frustum[0][3] + frustum[3][3];
	plane[0] = left;

	Plane right;
	right.a = -frustum[0][0] + frustum[3][0];
	right.b = -frustum[0][1] + frustum[3][1];
	right.c = -frustum[0][2] + frustum[3][2];
	right.d = -frustum[0][3] + frustum[3][3];
	plane[1] = right;

	Plane bottom;
	bottom.a = frustum[1][0] + frustum[3][0];
	bottom.b = frustum[1][1] + frustum[3][1];
	bottom.c = frustum[1][2] + frustum[3][2];
	bottom.d = frustum[1][3] + frustum[3][3];
	plane[2] = bottom;

	Plane top;
	top.a = -frustum[1][0] + frustum[3][0];
	top.b = -frustum[1][1] + frustum[3][1];
	top.c = -frustum[1][2] + frustum[3][2];
	top.d = -frustum[1][3] + frustum[3][3];
	plane[3] = top;

	Plane close;
	close.a = frustum[2][0] + frustum[3][0];
	close.b = frustum[2][1] + frustum[3][1];
	close.c = frustum[2][2] + frustum[3][2];
	close.d = frustum[2][3] + frustum[3][3];
	plane[4] = close;

	Plane away;
	away.a = frustum[2][0] + frustum[3][0];
	away.b = frustum[2][1] + frustum[3][1];
	away.c = frustum[2][2] + frustum[3][2];
	away.d = frustum[2][3] + frustum[3][3];
	plane[5] = away;

	for (int i = 0; i < 6; i++)
		plane[i].normalize();
}

bool Frustum::IsPointInside(glm::vec3 position)
{
	for (int i = 0; i < 6; i++)
	{
		float dot = plane[i].a * position.x +
			plane[i].b * position.y +
			plane[i].c * position.z +
			plane[i].d * 1.f;

		if (dot < 0.f)
			return false;
	}

	return true;
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
