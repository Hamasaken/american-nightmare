#include "MusicParticle.h"

void MusicParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, float angle, float strength)
{
	// Setting parameters
	isDead = false;
	float randomizedAngle = angle + randBetweenF(-0.45f, 0.45f);

	vertex.setPosition(glm::vec3(position.x + cos(randomizedAngle) * randBetweenF(0.65f, 1.0f), position.y + sin(randomizedAngle) * randBetweenF(0.65f, 1.0f), 0));
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(-randomizedAngle);

	// Setting some random variables
	lifeTime = MUSIC_LIFETIME;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(0.f);
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
}