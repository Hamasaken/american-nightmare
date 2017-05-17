#ifndef BLOODPARTICLE_H
#define BLOODPARTICLE_H

#include "Particle.h"

// BLOOD PARTICLES DEFAULTS
#define BLOOD_DEFAULT_COLOR		glm::vec4(0.80f, 0.1f, 0.05f, 1.f)
#define BLOOD_DEFAULT_AMOUNT	25
#define BLOOD_DEFAULT_STRENGTH	0.08f
#define BLOOD_SIZE				randBetweenF(0.4f, 0.9f)
#define BLOOD_VELOCITY			randBetweenF(-0.025f, 0.025f)
#define BLOOD_VELOCITY_FALL_OFF	randBetweenF(0.25f, 0.50f)
#define BLOOD_LIFETIME			randBetweenF(100.f, 350.f)

class BloodParticle : public Particle
{
public:

	////////////////////////////////////////////////////////////
	// \brief Initializes the particle with a position and color
	// \param position The starting position of the particle
	// \param color The starting color of the particle
	// \param size The size in w/h of the particle quad
	// \param angle The angle of the impact in radians
	// \param strength Impact strength of the hit (amount of dmg done)
	////////////////////////////////////////////////////////////
	virtual void Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, float angle, float strength);

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

#endif // !BLOODPARTICLE_H
