#include "Bar.h"

Bar::Bar() : Object() { }

Bar::Bar(const Bar & other) { }

Bar::~Bar() { }

bool Bar::Start(float &value, float maxValue, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, const MeshManager::Mesh* mesh)
{
	// Adding mesh and material
	if (!Object::Start(mesh, material))
		return false;

	// Visual placement
	this->startPosition = position;
	this->startSize = size;
	this->position = position;
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1 * size.x, 1 * size.y, 1);

	// Procent
	this->value = &value;
	this->maxValue = maxValue;
	this->procent = 0;
	this->showProcent = 0;

	return true;
}

void Bar::Stop()
{
	Object::~Object();
}

void Bar::Update(GLfloat deltaT)
{
	procent = (*value / maxValue) * 100.f;
	if (showProcent != procent)
	{
		showProcent += (procent - showProcent) * 0.05f;
		this->setScale(glm::vec3((showProcent / 100.f) * startSize.x, startSize.y, 1.f));
	}
}

void Bar::Draw()
{
	Object::Draw();
}

glm::vec3 Bar::getStartPosition() { return startPosition; }
int Bar::getProcent() { return procent; }
float Bar::getAlpha() { return alpha; }
void Bar::setAlpha(float alpha) { this->alpha = alpha; }
