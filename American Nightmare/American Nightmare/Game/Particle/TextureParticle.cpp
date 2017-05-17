#include "TextureParticle.h"

void TextureParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size)
{
	// Setting parameters
	isDead = false;
	rotation = randBetweenF(0.f, 360.f);

	// Making vertex
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(rotation);

	// Setting some random variables
	lifeTime = TEXTURE_LIFETIME;
	rotationSpeed = TEXTURE_ROTATION;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(TEXTURE_VELOCITY, TEXTURE_VELOCITY, randBetweenF(-0.0035f, 0.0035f));
}

void TextureParticle::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = (lifeTime - lifeTimeStart / 1.5f) / lifeTimeStart;
	vertex.a = (alpha) * TEXTURE_BLENDING;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		isDead = true;

	// Adds velocity fall-off for realistic effect
	rotationSpeed += (0.f - rotationSpeed) * TEXTURE_ROTATION_FALL_OFF;
	velocity += (glm::vec3(0, 0, 0) - velocity) * TEXTURE_VELOCITY_FALL_OFF;

	rotation += rotationSpeed * deltaT;

	// Moves the particle with velocity
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
	vertex.setRotation(rotation);
}

void SmokeParticle::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = (lifeTime - lifeTimeStart / 1.5f) / lifeTimeStart;
	vertex.a = (alpha)* TEXTURE_BLENDING;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		isDead = true;

	// Adds velocity fall-off for realistic effect
	rotationSpeed += (0.f - rotationSpeed) * TEXTURE_ROTATION_FALL_OFF;
	velocity += (glm::vec3(0, 0, 0) - velocity) * TEXTURE_VELOCITY_FALL_OFF;

	rotation += rotationSpeed * deltaT;

	// Moves the particle with velocity
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
	vertex.setRotation(rotation);
}