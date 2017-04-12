#include "Object.h"

Object::Object()
{ 
	model = nullptr;
//	texture = nullptr;
}

Object::Object(const Object& other) { }

Object::~Object() { }

bool Object::Start(std::string modelName, std::string textureName)
{
	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	// Creating model
	model = new Model();
	if (model == nullptr) return false;
	if (!model->Start(modelName)) return false;
	
	// Creating texture
//	texture = new Texture();
//	if (texture == nullptr) return false;
//	if (!texture->Start(textureName)) return false;

	texture = loadTexture(textureName);

	// TEMPORARY
	//model->BuildTriangle(openGL);
	//model->BuildQuad(openGL);
	model->BuildQuadTexture();

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

GLuint Object::loadTexture(std::string inImage)
{

	sf::Image* sfImage = new sf::Image();
	if (!sfImage->loadFromFile(inImage))
	{
		throw std::runtime_error("Could not load texture");
	}

	if (sfImage != nullptr)
	{
		GLuint glTexture;

		glGenTextures(1, &glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sfImage->getSize().x, sfImage->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, sfImage->getPixelsPtr());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		sfImage->~Image();
		delete sfImage;

		return glTexture;
	}

	return -1;
}

void Object::Update() { }

void Object::Draw()
{
	model->Draw();
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
GLuint Object::getTexture() const {	return texture; }
