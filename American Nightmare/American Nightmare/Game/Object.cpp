#include "Object.h"

Object::Object()
{ 
	model = nullptr;
//	texture = nullptr;
}

Object::Object(const Object& other) { }

Object::~Object() { }

bool Object::Start(std::string modelName, const MaterialManager::Material* material, b2World& world, float x, float y, bool isDynamic)
{
	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	// Creating model
	model = new Model();
	if (model == nullptr) return false;
	if (!model->Start(modelName)) return false;

	this->material = material;
	model->BuildQuadTexture();

	//Physics
	bodyDef.fixedRotation = true;
	bodyDef.position = b2Vec2(x, -y);
	bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody;
	body = world.CreateBody(&bodyDef);
	shape.SetAsBox(1.f, 1.f); // Creates a box shape. Divide your desired width and height by 2.

	fixtureDef.density = 0.f;  // Sets the density of the body
	fixtureDef.friction = 10.0f;
	fixtureDef.shape = &shape; // Sets the shape
	body->CreateFixture(&fixtureDef); // Apply the fixture definition

	return true;
}

void Object::Stop()
{
	// Unloading the model
	if (model != nullptr)
	{ 
		model->Stop();
		delete model;
		model = nullptr;
	}

	// Unloading the texture
//	if (texture != nullptr)
//	{
//		texture->Stop();
//		delete texture;
//		texture = nullptr;
//	}
}

void Object::Update(GLint deltaT) 
{

}

void Object::Draw()
{
	model->Draw();
}

void Object::setPosition(glm::vec3 position) { this->position = position; }
glm::vec3 Object::getPosition() const { return position; }
void Object::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
glm::vec3 Object::getRotation() const { return rotation; }
glm::vec3 Object::getRotationInRadians() const { return glm::vec3(rotation * (3.141592654f / 180.0f)); }
void Object::setScale(glm::vec3 scale) 
{
	this->scale = scale;

	shape.SetAsBox(scale.x, scale.y); // Creates a box shape. Divide your desired width and height by 2.
	fixtureDef.shape = &shape; // Sets the shape
	body->CreateFixture(&fixtureDef); // Apply the fixture definition
}

glm::vec3 Object::getScale() const { return scale; }
void Object::setShader(GLuint shader) { this->shader = shader; }
GLuint Object::getShader() const { return shader; }
GLuint Object::getTexture() const {	return texture; }
GLuint Object::getTextureID() const { return material->getTextureID(); }
void Object::SetAsBoxbox(float x, float y)
{
	shape.SetAsBox(x / 2, y / 2);
}
