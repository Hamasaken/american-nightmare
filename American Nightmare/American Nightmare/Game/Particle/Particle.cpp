#include "Particle.h"

Particle::Particle() { }

Particle::Particle(const Particle & other) { }

Particle::~Particle() { }

void Particle::Start(glm::vec3 position, glm::vec4 color)
{
	// Setting parameters
	isDead = false;
	vertex.setPosition(position);
	vertex.setColor(color);

	// Setting some random variables
	lifeTime = PARTICLE_LIFETIME;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(VELOCITY, VELOCITY, VELOCITY);
}

void Particle::Stop() { }

void Particle::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = lifeTime / lifeTimeStart;
	vertex.a = alpha;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		isDead = true;

	// Adds velocity fall-off for realistic effect
	velocity += (glm::vec3(0, -0.0035, 0) - velocity) * VELOCITY_FALL_OFF;

	// Moves the particle with velocity and frametime
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
}

Vertex* Particle::getAsVertex() { return &vertex; }

bool Particle::getIsDead() { return isDead; }
