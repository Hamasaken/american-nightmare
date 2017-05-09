#include "Hitbox.h"

Hitbox::Hitbox()
{
	body = nullptr;
}

Hitbox::Hitbox(const Hitbox & other) { }

Hitbox::~Hitbox() { }

bool Hitbox::InitializeHitbox(b2World* world)
{
	// Checking if world is created
	if (world == nullptr) return false;

	// Adding body to world
	AddBodyToWorld(world, glm::vec2(1.f, 1.f), b2_dynamicBody, false);

	// Creating shape for body
	ModifyShape(glm::vec2(1.f, 1.f), b2Shape::e_polygon, 0.f, 10.f);

	return true;
}

bool Hitbox::InitializeHitbox(b2World* world, glm::vec2 position, glm::vec2 size, b2BodyType type, b2Shape::Type shapeType, float density, float friction, bool isBullet)
{
	// Checking if world is created
	if (world == nullptr) return false;

	// Adding body to world
	AddBodyToWorld(world, position, type, isBullet);

	// Creating shape for body
	ModifyShape(size, shapeType, density, friction);

	return true;
}

void Hitbox::Stop()
{
	if (body != nullptr)
	{
		body->Dump();
		body = nullptr;
	}
}

void Hitbox::AddBodyToWorld(b2World* world, glm::vec2 position, b2BodyType type, bool isBullet)
{
	// Creating a new body and deleting old if needed
	if (body != nullptr) body->Dump();

	// Adding body to the world object
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position = b2Vec2(position.x, position.y);
	bodyDef.bullet = isBullet;
	bodyDef.active = true;
	body = world->CreateBody(&bodyDef);
}

void Hitbox::ModifyShape(glm::vec2 size, b2Shape::Type shapeType, float density, float friction)
{
	// Creating shape for body
	b2PolygonShape shape;
	shape.m_type = shapeType;
	shape.SetAsBox(size.x, size.y); // half the total size here

	// Creating the fixture
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = density;		// in kg/m^2
	fixture.friction = friction;	// friction [0:1]
	fixture.restitution = NULL;		// bouncy ball [0:1]
	body->CreateFixture(&fixture);
}

b2Body * Hitbox::getBody()
{
	return body;
}

glm::vec2 Hitbox::getPosition()
{
	return glm::vec2(body->GetPosition().x, body->GetPosition().y);
}