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
	// Setting position at origin
	position = glm::vec3(0, 0, 0);

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

void Object::Draw()
{
	model->Draw(openGL);
}