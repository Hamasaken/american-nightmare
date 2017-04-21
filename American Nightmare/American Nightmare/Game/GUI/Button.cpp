#include "Button.h"

Button::Button() : Object() { }

Button::Button(const Button & other) { }

Button::~Button() { }

bool Button::Start(glm::vec2 screenSize, glm::vec2 position, glm::vec2 size, glm::vec4 color, std::string fontName, float characterSize)
{
	// Setting starting variables and inserting parameters
	this->position = glm::vec3(position.x / (20.f / 1.11777), - position.y / (20.f / 1.12), 0.f);
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1, 1, 1);
	this->screenSize = screenSize;
	this->size = size;
	this->color = color;

	// Creating model object
	model = new Model();
	if (model == nullptr) return false;

	// Creating text object if wanted
	text = nullptr;
	if (!fontName.empty())
	{
		text = new Text();
		if (text == nullptr) return false;
		if (!text->Start(screenSize, fontName, characterSize, this->position, this->rotation, this->scale))
			return false;
	}

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
//	Object::Draw();

	// Drawing text
	if (text != nullptr)
		text->Draw();
}

void Button::setState(State state) { this->state = state; }

void Button::setSize(glm::vec2 size) { this->size = size; UpdateQuad(); }

void Button::setColor(glm::vec4 color) { this->color = color; UpdateQuad(); }

Button::State Button::getState() { return state; }

Text* Button::getText() { return text; }

glm::vec2 Button::getSize() { return size; }

glm::vec4 Button::getColor() { return color; }
