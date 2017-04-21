#include "Button.h"

Button::Button() : Object() { }

Button::Button(const Button & other) { }

Button::~Button() { }

bool Button::Start(glm::vec2 screenSize, glm::vec2 position, glm::vec2 size, std::string textureName, glm::vec4 color)
{
	Object::Start("", textureName);

	// Setting starting variables and inserting parameters
	this->position = fromScreenToWorld(position);
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1, 1, 1);
	this->screenSize = screenSize;
	this->size = size;
	this->color = color;

	// Creating model object
	model = new Model();
	if (model == nullptr) return false;

	// Updating quad model
	UpdateQuad();

	return true;
}

bool Button::isMouseInside()
{
	glm::vec2 mousePosition = glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	return (mousePosition.x > position.x && mousePosition.x < position.x + size.x &&
		mousePosition.y > position.y && mousePosition.y < position.y + size.y);
}

void Button::Update(GLint deltaT)
{
	// Checking if pressed or not
	if (state == State::Pressed)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			state = isMouseInside() ? State::Released : State::Nothing;
	}
	else
	{
		if (isMouseInside())
		{
			state = sf::Mouse::isButtonPressed(sf::Mouse::Left) ? State::Pressed : State::Hovering;
		}
		else
			state = State::Nothing;
	}
}

void Button::UpdateQuad()
{
	// Updating vertices with new variables
	model->BuildQuad(screenSize, position, color, size);
}

void Button::Draw()
{
	// Draws the actual button quad
	Object::Draw();
}

void Button::setState(State state) { this->state = state; }

void Button::setSize(glm::vec2 size) { this->size = size; UpdateQuad(); }

void Button::setColor(glm::vec4 color) { this->color = color; UpdateQuad(); }

Button::State Button::getState() { return state; }

glm::vec2 Button::getSize() { return size; }

glm::vec4 Button::getColor() { return color; }
