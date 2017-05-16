#ifndef DUSTPARTICLE_H
#define DUSTPARTICLE_H

#include "Particle.h"

#define DUST_VELOCITY			randBetweenF(-0.05f, 0.05f)
#define DUST_VELOCITY_FALL_OFF	randBetweenF(0.15f, 0.225f)

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
};

#endif // !DUSTPARTICLE_H
