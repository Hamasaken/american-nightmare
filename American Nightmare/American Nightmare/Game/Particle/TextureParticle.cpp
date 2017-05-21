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

void SmokeParticle::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size)
{
	// Setting parameters
	isDead = false;
	rotation = randBetweenF(0.f, 360.f);
	startPosition = position;

	// Making vertex
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(glm::vec2(randBetweenF(0.5f, 1.0f), randBetweenF(0.5f, 1.0f)));
	vertex.setRotation(rotation);
	vertex.a = SMOKE_TEXTURE_ALPHA;

	// Setting some random variables
	rotationSpeed = SMOKE_TEXTURE_ROTATION;
	velocity = glm::vec3(SMOKE_TEXTURE_VELOCITY, SMOKE_TEXTURE_VELOCITY, randBetweenF(-0.00075f, 0.00075f));
}

void SmokeParticle::Update(GLfloat deltaT)
{
	// Adds velocity fall-off for realistic effect
	rotation += rotationSpeed * deltaT;

	// Trying to force particle to move to starting position
	glm::vec3 currentPosition = glm::vec3(vertex.x, vertex.y, vertex.z);
	float angleToStartingPoint = getAngleFromTwoPoints(startPosition, currentPosition);
	glm::vec3 velocityToStartingPoint = glm::vec3(cos(angleToStartingPoint) * SMOKE_TEXTURE_VELOCITY * 2, sin(angleToStartingPoint) * SMOKE_TEXTURE_VELOCITY * 2, 0);
	velocity += (velocityToStartingPoint - velocity) * SMOKE_TEXTURE_PULL;

	vertex.setPosition(currentPosition + velocity * deltaT);
	vertex.setRotation(rotation);
}

void SmokeSignal::Reset()
{
	lifeTime = lifeTimeStart;
	vertex.setPosition(startPosition);
	vertex.setSize(startSize);
}

void SmokeSignal::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, float angle)
{
	// Setting parameters
	isDead = false;
	rotation = angle;

	// Making vertex
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(rotation);

	// Setting some random variables
	lifeTime = SIGNAL_LIFETIME;
	rotationSpeed = TEXTURE_ROTATION;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(SIGNAL_DEFAULT_VELOCITY * sin(rotation), SIGNAL_DEFAULT_VELOCITY * cos(rotation), randBetweenF(-0.00075f, 0.00075f));

	this->startSize = size;
	this->startPosition = position;
}

void SmokeSignal::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = (lifeTime - lifeTimeStart / 1.5f) / lifeTimeStart;
	vertex.a = (alpha)* TEXTURE_BLENDING;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		Reset();

	// Makes the particles bigger and bigger
	vertex.w *= SIGNAL_SIZE_MULTIPLIER;
	vertex.h *= SIGNAL_SIZE_MULTIPLIER;

	velocity += (glm::vec3(0, 0, 0) - velocity) * TEXTURE_VELOCITY_FALL_OFF;

	// Moves the particle with velocity
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
}