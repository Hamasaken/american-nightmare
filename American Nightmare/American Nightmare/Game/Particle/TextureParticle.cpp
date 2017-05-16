#include "TextureParticle.h"

void TextureParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size)
{
	// Setting parameters
	isDead = false;

	// Making vertex
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(randBetweenF(0.f, 360.f));

	// Setting some random variables
	lifeTime = TEXTURE_LIFETIME;
	rotationSpeed = TEXTURE_ROTATION;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(TEXTURE_VELOCITY, TEXTURE_VELOCITY, randBetweenF(-0.01f, 0.01f));
}

void TextureParticle::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = lifeTime / lifeTimeStart;
	vertex.a = alpha;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		isDead = true;

	// Adds velocity fall-off for realistic effect
	rotationSpeed += (0.f - rotationSpeed) * TEXTURE_ROTATION_FALL_OFF;
	velocity += (glm::vec3(0, 0, 0) - velocity) * TEXTURE_VELOCITY_FALL_OFF;

	// Moves the particle with velocity
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
}
