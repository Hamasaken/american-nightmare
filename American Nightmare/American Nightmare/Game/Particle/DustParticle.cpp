#include "DustParticle.h"

void DustParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size)
{
	// Setting parameters
	isDead = false;
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(0.f);

	this->angle = randBetweenF(0, 2* glm::pi<float>());

	// Setting some random variables
	velocity = glm::vec3(cos(angle + randBetweenF(-0.45f, 0.45f)) * DUST_VELOCITY, sin(angle + randBetweenF(-0.45f, 0.45f)) * DUST_VELOCITY, DUST_VELOCITY);
}

void DustParticle::Update(GLfloat deltaT)
{
	// Moves the particle with velocity and frametime
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
}