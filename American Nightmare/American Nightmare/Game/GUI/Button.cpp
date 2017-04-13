#include "Button.h"

Button::Button() : Object() { }

Button::Button(const Button & other) { }

Button::~Button() { }

bool Button::Start(glm::vec2 position, glm::vec2 size, glm::vec4 color)
{
	// Setting starting variables and inserting parameters
	this->position = glm::vec3(position.x, position.y, 0);
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1, 1, 1);
	this->size = size;
	this->color = color;

	// Creating model
	model = new Model();
	if (model == nullptr) return false;

	UpdateQuad();

	return true;
}

void Button::Update(GLint deltaT)
{
	// Checking if pressed or not
}

void Button::UpdateQuad()
{
	// Updating vertices with new variables
	model->BuildQuad(this->position, color, size);
}

void Button::setState(State state) { this->state = state; }

void Button::setSize(glm::vec2 size) { this->size = size; UpdateQuad(); }

void Button::setColor(glm::vec4 color) { this->color = color; UpdateQuad(); }

Button::State Button::getState() { return state; }

glm::vec2 Button::getSize() { return size; }

glm::vec4 Button::getColor() { return color; }
