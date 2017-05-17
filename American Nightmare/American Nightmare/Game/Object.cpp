#include "Object.h"

Object::Object()
{ 
	model = nullptr;
	material = nullptr;
}

Object::Object(const Object& other) { }

Object::~Object() { }

bool Object::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material)
{
	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	// Adding model 
	this->model = mesh->model;
	if (model == nullptr)
		return false;

	// Adding material
	this->material = material;
	if (material == nullptr)
		return false;

	return true;
}

void Object::Update(GLint deltaT) { }

void Object::Draw()
{
	model->Draw();
}

void Object::setPosition(glm::vec3 position) { this->position = position; }
glm::vec3 Object::getPosition() const { return position; }
glm::vec3 Object::getCenter() const { return glm::vec3(position.x - scale.x / 2, position.y + scale.y / 2, position.z + scale.z / 2); }
void Object::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
glm::vec3 Object::getRotation() const { return rotation; }
void Object::setScale(glm::vec3 scale) { this->scale = scale; }
glm::vec3 Object::getScale() const { return scale; }
void Object::setShader(GLuint shader) { this->shader = shader; }
GLuint Object::getShader() const { return shader; }
GLuint Object::getTextureID() const { return material->getTextureID(); }
const MaterialManager::Material* Object::getMaterial() const { return material; }