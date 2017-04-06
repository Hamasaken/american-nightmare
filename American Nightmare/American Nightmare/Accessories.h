#ifndef ACCESSORIES_H
#define ACCESSORIES_H

// Including various opengl math classes & functions
#include <glm/glm.hpp>	
#include <glm/mat4x4.hpp>		// 4x4 matrices
#include <glm/gtc/matrix_transform.hpp>	// matrix stuff
#include <glm/gtc/constants.hpp>	// pi
#include <glm/gtc/type_ptr.hpp>		// value_ptr
#include <glm/gtx/rotate_vector.hpp>	// rotating vectors and matrices

// Including full smfl libary
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

// Various includes
#include <string>

// Vertex Struct for vertex buffers, etc
struct Vertex
{
	void setPosition(glm::vec3 position)
	{
		x = position.x;
		y = position.y;
		z = position.z; 
	}

	void setColor(glm::vec3 color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
	}
	float x, y, z;
	float r, g, b; 
};

#endif // !ACCESSORIES_H
