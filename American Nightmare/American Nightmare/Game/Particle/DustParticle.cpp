#include "DustParticle.h"

void DustParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size)
{
	// Setting parameters
	this->startPosition = position;
	isDead = false;
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(0.f);

	this->angle = randBetweenF(0, 2* glm::pi<float>());

	// Setting some random variables
	velocity = glm::vec3(cos(angle + randBetweenF(-0.45f, 0.45f)) * LIGHT_DUST_VELOCITY, sin(angle + randBetweenF(-0.45f, 0.45f)) * LIGHT_DUST_VELOCITY, LIGHT_DUST_VELOCITY);
}

void DustParticle::Update(GLfloat deltaT)
{
	// Moves the particle with velocity and frametime
	velocity.x += LIGHT_DUST_VELOCITY;
	velocity.y += LIGHT_DUST_VELOCITY;

	// Gets the current position of this particle
	glm::vec3 currentPosition = glm::vec3(vertex.x, vertex.y, vertex.z);

	// Trying to force particle to move to starting position
	float angleToStartingPoint = getAngleFromTwoPoints(startPosition, currentPosition);
	glm::vec3 velocityToStartingPoint = glm::vec3(cos(angleToStartingPoint) * LIGHT_DUST_VELOCITY * 2, sin(angleToStartingPoint) * LIGHT_DUST_VELOCITY * 2, 0);
	velocity += (velocityToStartingPoint - velocity) * LIGHT_DUST_PULLING_STRENGTH;

	vertex.setPosition(currentPosition + velocity * deltaT);
}