#ifndef DUSTPARTICLE_H
#define DUSTPARTICLE_H

#include "Particle.h"

#define LIGHT_DUST_DEFAULT_AMOUNT		50
#define LIGHT_DUST_DEFAULT_COLOR		glm::vec4(0.4, 0.4, 0.4, 1.f)
#define LIGHT_DUST_SIZE					randBetweenF(0.10f, 0.20f)
#define LIGHT_DUST_VELOCITY				randBetweenF(-0.0001f, 0.0001f)
#define LIGHT_DUST_PULLING_STRENGTH		0.03f
#define LIGHT_DUST_DEFAULT_DIMENSIONS	glm::vec3(40.f, 25.f, 0.f)
#define LIGHT_DUST_DEFAULT_CENTER		glm::vec3(0, 0, 0)

struct DustParticle : public Particle
{
public:

	////////////////////////////////////////////////////////////
	// \brief Initializes the particle with a position and color
	// \param position The starting position of the particle
	// \param color The starting color of the particle
	// \param size The size in w/h of the particle quad
	////////////////////////////////////////////////////////////
	virtual void Start(glm::vec3 position, glm::vec4 color, glm::vec2 size);

	////////////////////////////////////////////////////////////
	// \brief Updates various variables in the pixel
	//	Removes lifetime from particle and makes it dead if not time left
	//	Also adds velocity fall-off for a more realistic effect
	// \param deltaT The time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	virtual void Update(GLfloat deltaT);

protected:
	float angle;
	glm::vec3 startPosition;
};

#endif // !DUSTPARTICLE_H
