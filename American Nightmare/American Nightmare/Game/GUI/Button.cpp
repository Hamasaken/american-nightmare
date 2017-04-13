#include "Button.h"

Button::Button() : Object() { }

Button::Button(const Button & other) { }

Button::~Button() { }

void Button::Start(glm::vec2 position, glm::vec2 size)
{
	this->position = glm::vec3(position.x, position.y, 0);
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1, 1, 1);

	model->BuildQuad(this->position, size);
}

void Button::Update(GLint deltaT)
{

}

Button::State Button::getState()
{
	return state;
}

void Button::setState(State state) { this->state = state; }
