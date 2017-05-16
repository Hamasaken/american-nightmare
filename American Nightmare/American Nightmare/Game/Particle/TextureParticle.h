#ifndef TEXTUREPARTICLE_H
#define TEXTUREPARTICLE_H

#include "Particle.h"

// TEXTURE PARTICLES DEFAULTS
#define TEXTURE_DEFAULT_COLOR		glm::vec4(1.f, 1.f, 1.f, 1.f)
#define TEXTURE_DEFAULT_AMOUNT		10
#define TEXTURE_SIZE				randBetweenF(0.5f, 1.5f)
#define TEXTURE_VELOCITY			randBetweenF(-0.001f, 0.001f)
#define TEXTURE_VELOCITY_FALL_OFF	randBetweenF(0.005f, 0.01f)
#define TEXTURE_LIFETIME			randBetweenF(1500.f, 3000.f)
#define TEXTURE_ROTATION			randBetweenF(-0.001f, 0.001f)
#define TEXTURE_ROTATION_FALL_OFF	randBetweenF(0.005f, 0.005f)
#define TEXTURE_BLENDING			0.55f

class TextureParticle : public Particle
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
	float rotation;
	float rotationSpeed;
};

#endif // !TEXTUREPARTICLE_H
