#include "TextureParticle.h"

void TextureParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, GLuint texture)
{
	// Getting texture
	this->texture = texture;

	// Setting parameters
	isDead = false;
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);

	// Setting some random variables
	lifeTime = TEXTURE_LIFETIME;
	lifeTimeStart = lifeTime;
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
	velocity += (glm::vec3(0, 0, 0) - velocity) * TEXTURE_VELOCITY_FALL_OFF;

	// Moves the particle with velocity and frametime
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
}

GLuint TextureParticle::getTexture() { return texture; }
