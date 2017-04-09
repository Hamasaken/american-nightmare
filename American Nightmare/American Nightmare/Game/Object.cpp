#include "Object.h"

Object::Object()
{ 
	openGL = nullptr;
	model = nullptr;
//	texture = nullptr;
}

Object::Object(const Object& other) { }

Object::~Object() { }

bool Object::Start(OpenGL* openGL, std::string modelName, std::string textureName)
{
	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	// Grabbing the openGL ptr
	this->openGL = openGL;

	// Creating model
	model = new Model();
	if (model == nullptr) return false;
	if (!model->Start(openGL, modelName)) return false;
	
	// Creating texture
//	texture = new Texture();
//	if (texture == nullptr) return false;
//	if (!texture->Start(textureName)) return false;

	// TEMPORARY
	//model->BuildTriangle(openGL);
	model->BuildQuad(openGL);

	return true;
}

void Object::Stop()
{
	// Unloading the model
	if (model != nullptr)
	{ 
		model->Stop(openGL);
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

	// Removing the ptr to openGL functions
	openGL = nullptr;
}

void Object::Update() { }

void Object::Draw()
{
	model->Draw(openGL);
}

void Object::setPosition(glm::vec3 position) { this->position = position; }
glm::vec3 Object::getPosition() const { return position; }
void Object::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
glm::vec3 Object::getRotation() const { return rotation; }
glm::vec3 Object::getRotationInRadians() const { return glm::vec3(rotation * (3.141592654f / 180.0f)); }
void Object::setScale(glm::vec3 scale) { this->scale = scale; }
glm::vec3 Object::getScale() const { return scale; }
void Object::setShader(GLuint shader) { this->shader = shader; }
GLuint Object::getShader() const { return shader; }
