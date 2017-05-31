#ifndef TEXTUREPARTICLE_H
#define TEXTUREPARTICLE_H

#include "Particle.h"

// TEXTURE PARTICLES DEFAULTS
#define TEXTURE_DEFAULT_COLOR		glm::vec4(1.f, 1.f, 1.f, 1.f)
#define TEXTURE_DEFAULT_AMOUNT		10
#define TEXTURE_SIZE				randBetweenF(0.25f, 0.50f)
#define TEXTURE_VELOCITY			randBetweenF(-0.001f, 0.001f)
#define TEXTURE_VELOCITY_FALL_OFF	randBetweenF(0.005f, 0.01f)
#define TEXTURE_LIFETIME			randBetweenF(1500.f, 3000.f)
#define TEXTURE_ROTATION			randBetweenF(-0.001f, 0.001f)
#define TEXTURE_ROTATION_FALL_OFF	randBetweenF(0.005f, 0.005f)
#define TEXTURE_BLENDING			0.55f

// TEXTURE SMOKE DEFAULTS
#define SMOKE_TEXTURE_ROTATION		randBetweenF(-0.0001f, 0.0001f)
#define SMOKE_TEXTURE_VELOCITY		randBetweenF(-0.00025f, 0.00025f)
#define SMOKE_TEXTURE_PULL			0.035f
#define SMOKE_TEXTURE_ALPHA			randBetweenF(0.025f, 0.10f)

// TEXTURE SMOKE SIGNAL DEFAULTS
#define SIGNAL_LIFETIME				randBetweenF(1500.f, 3000.f)
#define SIGNAL_DEFAULT_SIZE			randBetweenF(1.f, 1.25f)
#define SIGNAL_DEFAULT_AMOUNT		25
#define SIGNAL_DEFAULT_VELOCITY		randBetweenF(0.f, 0.0350f)
#define SIGNAL_SIZE_MULTIPLIER		0.965f

// NUTS AND BOLTS DEFAULTS
#define NUTS_DEFAULT_COLOR			glm::vec4(0.45f, 0.45f, 0.45f, 1.f)
#define NUTS_DEFAULT_AMOUNT			8
#define NUTS_SIZE					randBetweenF(0.20f, 0.30f)
#define NUTS_VELOCITY				randBetweenF(-0.0070f, 0.0070f)
#define NUTS_LIFETIME				randBetweenF(1000.f, 2000.f)
#define NUTS_ROTATION				randBetweenF(-0.009f, 0.009f)
#define NUTS_ROTATION_FALL_OFF		randBetweenF(0.0025f, 0.0025f)
#define NUTS_VELOCITY_FALL_OFF		randBetweenF(0.0085f, 0.010f)

class TextureParticle : public Particle
{
public:
	////////////////////////////////////////////////////////////
	// \brief Initializes the particle with a position and color
	// \param position The starting position of the particle
	// \param color The starting color of the particle
	// \param size The size in w/h of the particle quad
	// \param angle The angle of the impact in radians
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
	float rotation;
	float rotationSpeed;
};

class SmokeParticle : public TextureParticle
{
public:
	virtual void Start(glm::vec3 position, glm::vec4 color, glm::vec2 size);
	virtual void Update(GLfloat deltaT);
private:
	glm::vec3 startPosition;
};

class SmokeSignal : public TextureParticle
{
public:
	void Reset();
	void Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, float angle);
	void Update(GLfloat deltaT);

private:
	glm::vec2 startSize;
	glm::vec3 startPosition;
	float startAngle;
};


class NutsAndBolt : public TextureParticle
{
public:
	void Start(glm::vec3 position, glm::vec4 color, glm::vec2 size);
	void Update(GLfloat deltaT);
};


#endif // !TEXTUREPARTICLE_H
