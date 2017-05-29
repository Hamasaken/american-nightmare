#include "MusicParticle.h"

void MusicParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, float angle, float strength)
{
	// Setting parameters
	isDead = false;
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(angle);
	rotation = angle;

	// Setting some random variables
	lifeTime = MUSIC_LIFETIME;
	rotationSpeed = MUSIC_ROTATION;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(cos(angle + randBetweenF(-0.45f, 0.45f)) * strength, sin(angle + randBetweenF(-0.45f, 0.45f)) * strength, MUSIC_VELOCITY);
}

void MusicParticle::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = lifeTime / lifeTimeStart;
	vertex.a = alpha;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		isDead = true;

	// Adds rotation & velocity fall-off for realistic effectv
	rotationSpeed += (0.f - rotationSpeed) * MUSIC_ROTATION_FALL_OFF;
	velocity += (glm::vec3(0, 0, 0) - velocity) * MUSIC_VELOCITY_FALL_OFF;
	rotation += rotationSpeed * deltaT;

	// Moves the particle with velocity
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
	vertex.setRotation(rotation);
}