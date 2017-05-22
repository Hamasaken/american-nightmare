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
	ModifyShape(glm::vec2(1.f, 1.f), b2Shape::e_polygon, 0.f, 10.f, false);

	return true;
}

bool Hitbox::InitializeHitbox(b2World* world, glm::vec2 position, glm::vec2 size, b2BodyType type, b2Shape::Type shapeType, bool canRotate, float density, float friction, bool isBullet, bool isSensor)
{
	// Checking if world is created
	if (world == nullptr) return false;

	// Adding body to world
	AddBodyToWorld(world, position, type, canRotate, isBullet);

	// Creating shape for body
	ModifyShape(size, shapeType, density, friction, isSensor);
	
	return true;
}

bool Hitbox::InitializeHitboxVacuum(b2World* world, b2Body* player)
{
	if (world == nullptr) return false;

	//if (body != nullptr) body->Dump();
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.active = true;
	//bodyDef.position = b2Vec2(player->GetPosition().x + 2, player->GetPosition().y);
	//body = world->CreateBody(&bodyDef);
	//
	//b2Vec2 vertices[3];
	//vertices[0].Set(0.0f, 0.0f);
	//vertices[1].Set(2.0f, -0.25f);
	//vertices[2].Set(2.0f, 0.25f);
	//int32 count = 3;
	//
	//b2PolygonShape polygon;
	//polygon.m_type = b2Shape::e_polygon;
	//polygon.Set(vertices, count);
	//
	//b2FixtureDef fixture;
	//fixture.shape = &polygon;
	//fixture.isSensor = true;
	//body->CreateFixture(&fixture);
	//
	//body->SetGravityScale(0);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(player->GetPosition().x + 2, player->GetPosition().y);
	bodyDef.fixedRotation = false;
	bodyDef.active = true;

	body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 8;

	//b2Vec2 vertices[3];
	//vertices[0].Set(0.0f, 0.0f);
	//vertices[1].Set(2.0f, -0.25f);
	//vertices[2].Set(2.0f, 0.25f);
	//int32 count = 3;
	//
	//b2PolygonShape polygon;
	//polygon.m_type = b2Shape::e_polygon;
	//polygon.Set(vertices, count);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.isSensor = true;
	fixture = body->CreateFixture(&fixtureDef);

	body->SetGravityScale(0);
}

void Hitbox::Stop()
{
	if (body != nullptr)
	{
		body->Dump();
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
	body = world->CreateBody(&bodyDef);
}

void Hitbox::ModifyShape(glm::vec2 size, b2Shape::Type shapeType, float mass, float friction, bool isSensor)
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

b2Body * Hitbox::getBody()
{
	return body;
}

glm::vec2 Hitbox::getPosition()
{
	return glm::vec2(body->GetPosition().x, -body->GetPosition().y);
}