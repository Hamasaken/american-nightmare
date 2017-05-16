#ifndef TEXTUREPARTICLE_H
#define TEXTUREPARTICLE_H

#include "Particle.h"

// TEXTURE PARTICLES DEFAULTS
#define TEXTURE_DEFAULT_COLOR		glm::vec4(1.f, 1.f, 1.f, 1.f)
#define TEXTURE_DEFAULT_AMOUNT		10
#define TEXTURE_SIZE				1.f
#define TEXTURE_VELOCITY			randBetweenF(-0.01f, 0.01f)
#define TEXTURE_VELOCITY_FALL_OFF	randBetweenF(0.001f, 0.0067f)
#define TEXTURE_LIFETIME			randBetweenF(1500.f, 3000.f)
#define TEXTURE_ROTATION			randBetweenF(-0.25f, 0.25f)
#define TEXTURE_ROTATION_FALL_OFF	randBetweenF(0.35f, 0.50f)

struct TextureParticle : public Particle
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
	virtual void Start(glm::vec3 position, glm::vec4 color, glm::vec2 size);

	////////////////////////////////////////////////////////////
	// \brief Updates various variables in the pixel
	//	Removes lifetime from particle and makes it dead if not time left
	//	Also adds velocity fall-off for a more realistic effect
	// \param deltaT The time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	virtual void Update(GLfloat deltaT);

private:
	float rotationSpeed;
};

#endif // !TEXTUREPARTICLE_H
