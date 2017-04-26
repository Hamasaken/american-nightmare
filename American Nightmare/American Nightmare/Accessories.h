#ifndef ACCESSORIES_H
#define ACCESSORIES_H

#include <Windows.h>
#include <GL/glew.h>

// Including various opengl math classes & functions
#include <glm/glm.hpp>	
#include <glm/mat4x4.hpp>		// 4x4 matrices
#include <glm/gtc/matrix_transform.hpp>	// matrix stuff
#include <glm/gtc/constants.hpp>	// pi
#include <glm/gtc/type_ptr.hpp>		// value_ptr
#include <glm/gtx/rotate_vector.hpp>	// rotating vectors and matrices

// Including full smfl libary
#include <SFML\Audio.hpp>			// Sound and SFX
#include <SFML\Window\Keyboard.hpp>	// Input Keyboard	

// Various includes
#include <string>

// Paths
#define SHADER_PATH "Data/Graphics/Shaders/"
#define MODEL_PATH "Data/Graphics/Models/"
#define CUTSCENE_PATH "Data/Graphics/Cutscenes/"
#define TEXTURE_PATH "Data/Graphics/Textures/"
#define FONT_PATH "Data/Graphics/Fonts/"
#define ANIMATION_PATH "Data/Graphics/Animations/"
#define SFX_PATH "Data/Sound/SFX/"
#define MUSIC_PATH "Data/Sound/Music/"

// Global variables
#define GRAVITY 9.82f

// Functions
float randBetweenF(float low, float high);
glm::vec3 fromScreenToWorld(glm::vec2 position, glm::vec2 screenSize, glm::mat4 view, glm::mat4 projection);
glm::vec3 fromScreenToWorld(glm::vec2 position);

// Vertex Struct for vertex buffers, etc
struct Vertex
{
	void setPosition(glm::vec3 position)
	{
		x = position.x;
		y = position.y;
		z = position.z; 
	}

	void setColor(glm::vec4 color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	float x, y, z;
	float r, g, b, a; 
};

struct VertexUV
{
	void setPosition(glm::vec3 position)
	{
		x = position.x;
		y = position.y;
		z = position.z;
	}

	void setUV(glm::vec2 uv)
	{
		u = uv.x;
		v = uv.y;
	}

	void setNormal(glm::vec3 normal)
	{
		nx = normal.x;
		ny = normal.y;
		nz = normal.z;
	}

	float x, y, z;
	float u, v;
	float nx, ny, nz;
};

#endif // !ACCESSORIES_H
