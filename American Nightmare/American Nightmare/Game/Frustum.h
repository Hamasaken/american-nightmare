#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "../Accessories.h"

class Frustum
{
private:
	struct Plane 
	{ 
		float a, b, c, d; 
		void normalize() 
		{
			float d = sqrtf(a * a + b * b + c * c);
			a = a / d; b = b / d; c = c / d; d = d / d;
		}
	} ;
public:
	Frustum();
	Frustum(const Frustum& other);
	~Frustum();

	void Start(float screenDepth, glm::mat4 viewMatrix, glm::mat4 orthoMatrix);

	bool IsPointInside(glm::vec3 position);
	bool IsCubeInside(glm::vec3 center, float side);
	bool IsSphereInside(glm::vec3 center, float radius);
	bool IsRectangleInside(glm::vec3 center, glm::vec3 dimensions);

private:
	Plane plane[6];
};

#endif // !FRUSTUM_H

