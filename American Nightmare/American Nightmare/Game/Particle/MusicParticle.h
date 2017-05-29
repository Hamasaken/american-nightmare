#ifndef MUSICPARTICLE_H
#define MUSICPARTICLE_H

#include "Particle.h"

// MUSIC PARTICLES DEFAULTS
#define MUSIC_DEFAULT_COLOR		glm::vec4(0.5f)
#define MUSIC_DEFAULT_AMOUNT	1
#define MUSIC_DEFAULT_STRENGTH	0.f
#define MUSIC_SIZE				randBetweenF(0.30f, 0.47f)
#define MUSIC_LIFETIME			randBetweenF(275.f, 456.f)

class MusicParticle : public Particle
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
};

#endif // !MUSICPARTICLE_H
