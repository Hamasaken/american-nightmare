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
	velocity = glm::vec3(TEXTURE_VELOCITY, TEXTURE_VELOCITY, randBetweenF(-0.0015f, 0.0015f));
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
	velocity = glm::vec3(SMOKE_TEXTURE_VELOCITY / 4, SMOKE_TEXTURE_VELOCITY / 4, randBetweenF(-0.00001f, 0.00001f));
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


void SmokePuff::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, float angle, float strength)
{
	// Setting parameters
	isDead = false;
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(0.f);

	// Setting some random variables
	lifeTime = TEXTURE_LIFETIME / 4;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(cos(angle + randBetweenF(-0.35f, 0.35f)) * strength / 1.5f, sin(angle + randBetweenF(-0.35f, 0.35f)) * strength / 1.5f, TEXTURE_VELOCITY);
}

void SmokePuff::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = (lifeTime - lifeTimeStart / 1.5f) / lifeTimeStart;
	vertex.a = (alpha)* TEXTURE_BLENDING;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		isDead = true;

	// Adds velocity fall-off for realistic effect
	velocity += (glm::vec3(0, 0, 0) - velocity) * TEXTURE_VELOCITY_FALL_OFF;

	// Moves the particle with velocity and frametime
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
}

void SmokeSignal::Reset()
{
	// Setting some random variablesr
	rotation = rand() % 360 + 1;
	rotationSpeed = TEXTURE_ROTATION;
	velocity = glm::vec3(SIGNAL_DEFAULT_VELOCITY * cos(startAngle + randBetweenF(-0.45f, 0.45f)), SIGNAL_DEFAULT_VELOCITY * sin(startAngle + randBetweenF(-0.45f, 0.45f)), randBetweenF(-0.00075f, 0.00075f));

	lifeTime = lifeTimeStart;
	vertex.setPosition(startPosition);
	vertex.setSize(startSize);
	vertex.setRotation(rotation);
}

void SmokeSignal::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size, float angle)
{
	// Setting parameters
	isDead = false;
	rotation = rand() % 360 + 1;

	// Making vertex
	vertex.setPosition(position);
	vertex.setColor(color);
	vertex.setSize(size);
	vertex.setRotation(rotation);

	// Setting some random variables
	lifeTime = SIGNAL_LIFETIME;
	rotationSpeed = TEXTURE_ROTATION;
	lifeTimeStart = lifeTime;
	startOffset = randBetweenF(-0.45f, 0.45f);
	velocity = glm::vec3(SIGNAL_DEFAULT_VELOCITY * cos(angle + startOffset), SIGNAL_DEFAULT_VELOCITY * sin(angle + startOffset), randBetweenF(-0.00075f, 0.00075f));

	this->startAngle = angle;
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
	velocity.x *= 1 - abs(startOffset);

	rotation += rotationSpeed * deltaT;

	// Moves the particle with velocity & rotation
	vertex.setRotation(rotation);
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
}

void NutsAndBolt::Start(glm::vec3 position, glm::vec4 color, glm::vec2 size)
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
	lifeTime = NUTS_LIFETIME;
	rotationSpeed = NUTS_ROTATION * 2;
	lifeTimeStart = lifeTime;
	velocity = glm::vec3(NUTS_VELOCITY, NUTS_VELOCITY, randBetweenF(-0.025f, 0.025f));
}

void NutsAndBolt::Update(GLfloat deltaT)
{
	// Makes color alpha with the rest of lifetime
	float alpha = (lifeTime - lifeTimeStart / 1.5f) / lifeTimeStart;
	vertex.a = (alpha)* TEXTURE_BLENDING;

	// Removes from lifetime and checks if particle is dead
	lifeTime -= deltaT;
	if (lifeTime < NULL)
		isDead = true;

	// Adds velocity fall-off for realistic effect
	rotationSpeed += (0.f - rotationSpeed) * (NUTS_ROTATION_FALL_OFF / 3);
	velocity += (glm::vec3(0, -0.0350, 0) - velocity) * NUTS_VELOCITY_FALL_OFF;

	rotation += rotationSpeed * deltaT;

	// Moves the particle with velocity
	vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
	vertex.setRotation(rotation);
}