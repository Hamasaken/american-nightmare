#ifndef MUSICPARTICLE_H
#define MUSICPARTICLE_H

#include "Particle.h"

// MUSIC PARTICLES DEFAULTS
#define MUSIC_DEFAULT_COLOR		glm::vec4(0.70f, 0.50f, 0.10f, 0.8f)
#define MUSIC_DEFAULT_AMOUNT	1
#define MUSIC_DEFAULT_STRENGTH	0.00000001f
#define MUSIC_SIZE				randBetweenF(0.2f, 0.4f)
#define MUSIC_VELOCITY			randBetweenF(-0.00001f, 0.00001f)
#define MUSIC_VELOCITY_FALL_OFF	randBetweenF(0.003f, 0.005f)
#define MUSIC_LIFETIME			randBetweenF(175.f, 375.f)
#define MUSIC_ROTATION			randBetweenF(-0.0020f, 0.0020f)
#define MUSIC_ROTATION_FALL_OFF	randBetweenF(0.005f, 0.005f)

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

protected:
	float angle;
	float rotation;
	float rotationSpeed;
};

#endif // !MUSICPARTICLE_H
