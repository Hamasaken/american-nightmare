#include "Hitbox.h"

Hitbox::Hitbox()
{
	body = nullptr;
	fixture = nullptr;
}

Hitbox::Hitbox(const Hitbox & other) { }

Hitbox::~Hitbox() { }

bool Hitbox::InitializeHitbox(b2World* world)
{
	// Checking if world is created
	if (world == nullptr) return false;

	// Adding body to world
	AddBodyToWorld(world, glm::vec2(1.f, 1.f), b2_dynamicBody, false, false);

	// Creating shape for body
	ModifyRectangleShape(glm::vec2(1.f, 1.f), b2Shape::e_polygon, 2.f, 10.f, false);

	return true;
}

bool Hitbox::InitializeHitbox(b2World* world, glm::vec2 position, glm::vec2 size, b2BodyType type, b2Shape::Type shapeType, bool canRotate, float density, float friction, float radius, bool isBullet, bool isSensor)
{
	// Checking if world is created
	if (world == nullptr) return false;

	// Adding body to world
	AddBodyToWorld(world, position, type, canRotate, isBullet);

	// Creating shape for body
	if (shapeType == b2Shape::e_circle)			ModifyCircleShape(size, shapeType, density, friction, isSensor);
	else if (shapeType == b2Shape::e_polygon)	ModifyRectangleShape(size, shapeType, density, friction, isSensor);
	else return false;
	
	return true;
}

bool Hitbox::InitializeHitboxVacuum(b2World* world, b2Body* player)
{
	if (world == nullptr) return false;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(player->GetPosition().x, player->GetPosition().y);
	bodyDef.fixedRotation = false;
	bodyDef.active = true;

	body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 4;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.isSensor = true;
	fixture = body->CreateFixture(&fixtureDef);

	body->SetGravityScale(0);

	return true;
}

void Hitbox::Stop(b2World* world)
{
	if (body != nullptr)
	{
		body->SetUserData(nullptr);
	//	world->DestroyBody(body);
		body = nullptr;
	}
}

void Hitbox::AddBodyToWorld(b2World* world, glm::vec2 position, b2BodyType type, bool canRotate, bool isBullet)
{
	// Creating a new body and deleting old if needed
	if (body != nullptr)
	{
		if (fixture != nullptr)
			body->DestroyFixture(fixture);
		body->Dump();
	}

	// Adding body to the world object
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.bullet = isBullet;
	bodyDef.position = b2Vec2(position.x, -position.y);
	bodyDef.fixedRotation = canRotate;
	bodyDef.active = true;
	bodyDef.userData = this;
	body = world->CreateBody(&bodyDef);
}

void Hitbox::ModifyRectangleShape(glm::vec2 size, b2Shape::Type shapeType, float mass, float friction, bool isSensor)
{
	// Creating shape for body
	b2PolygonShape shape;
	shape.m_type = shapeType;
	shape.SetAsBox(size.x / 2, size.y / 2); // half the total size here

	// Creating the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = isSensor;
	fixtureDef.shape = &shape;
	fixtureDef.density = 4 * mass / (size.x * size.y);		// in kg/m^2
	fixtureDef.friction = friction;						// friction [0:1]
	fixtureDef.restitution = 0.0f;							// bouncy ball [0:1]
	fixture = body->CreateFixture(&fixtureDef);
//	body->SetTransform(b2Vec2(0, 0), 0.f);
}

void Hitbox::ModifyCircleShape(glm::vec2 radius, b2Shape::Type shapeType, float mass, float friction, bool isSensor)
{
	// Creating shape for body
	b2CircleShape shape;
	shape.m_type = shapeType;
	shape.m_radius = radius.x / 2;
	shape.m_p.Set(0, 0);

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = isSensor;
	fixtureDef.shape = &shape;
	fixtureDef.density = 4 * mass / (radius.x * radius.y);		// in kg/m^2
	fixtureDef.friction = friction;						// friction [0:1]
	fixtureDef.restitution = 0.0f;							// bouncy ball [0:1]
	fixture = body->CreateFixture(&fixtureDef);
}

b2Body * Hitbox::getBody()
{
	return body;
}

glm::vec2 Hitbox::getPosition()
{
	return glm::vec2(body->GetPosition().x, -body->GetPosition().y);
}