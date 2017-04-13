#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../Accessories.h"

#define VELOCITY		randBetweenF(-0.25f, 0.25f)
#define VELOCITY_FALL_OFF	randBetweenF(0.35f, 0.50f)
#define PARTICLE_LIFETIME	randBetweenF(500.f, 900.f)

struct Particle
{
public:
	Particle();
	Particle(const Particle& other);
	~Particle();

	////////////////////////////////////////////////////////////
	// \brief Initializes the particle with a position and color
	// \param position The starting position of the particle
	// \param color The starting color of the particle
	////////////////////////////////////////////////////////////
	virtual void Start(glm::vec3 position, glm::vec4 color);

	////////////////////////////////////////////////////////////
	// \brief Unloads stuff inside the particle
	// \note This one is empty, but might be needed for other particles
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Updates various variables in the pixel
	//	Removes lifetime from particle and makes it dead if not time left
	//	Also adds velocity fall-off for a more realistic effect
	// \param deltaT The time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	virtual void Update(GLfloat deltaT);

	////////////////////////////////////////////////////////////
	// \brief Gets the particle as a vertex for drawing with shader
	////////////////////////////////////////////////////////////
	Vertex getAsVertex();

	////////////////////////////////////////////////////////////
	// \brief Returns true if the particle is dead, otherwise false
	////////////////////////////////////////////////////////////
	bool getIsDead();

private:
	bool isDead;		//< If the particle is dead and should be removed
	GLfloat lifeTime;	//< How much time the particle have left
	Vertex vertex;		//< The position and color of the particle
	glm::vec3 velocity;	//< The current velocity of the particle
};

#endif // !PARTICLE_H
