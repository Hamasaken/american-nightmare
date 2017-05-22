#include "vacuum.h"

Vacuum::Vacuum()
{
}


Vacuum::~Vacuum()
{
	
}

void Vacuum::startVac(b2World* world, b2Body* player)
{
	Entity:Start(world, player);

	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	// Creating model
	model = new Model();
	if (model == nullptr);
	//if (!model->Start(modelName));

	this->material = material;
	model->BuildQuadTexture();

	hitbox->getBody()->SetUserData(this);
	//b2RevoluteJointDef jointDef;

	//jointDef.bodyA = player;
	//jointDef.bodyA = hitbox->getBody();

	//jointDef.localAnchorA.Set(0, 0);
	//jointDef.localAnchorB.Set(0, 0);

	//jointDef.collideConnected = false;

	////jointDef.Initialize(player, body, b2Vec2(0, 0));

	//joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

b2Body* Vacuum::getBody()const
{
	return hitbox->getBody();
}

void Vacuum::Update(b2Vec2 pos, GLint deltaT)
{
	/*glm::vec2 mouse = fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1920, 1080 }, glm::vec2{ 0, 0 });
	float vector = getAngleFromTwoPoints(glm::vec3(mouse.x, mouse.y, 0), glm::vec3(Pos.x, Pos.y, 0));
	int angel = radianToDegree(vector);*/

	//b2Vec2 pos2 = Pos;
	//pos2 = b2Vec2(pos2.x + (mouse.x * 2), pos2.y + (mouse.y * 2));

	getBody()->SetTransform(pos, 0);

	Entity::Update(deltaT);
}


