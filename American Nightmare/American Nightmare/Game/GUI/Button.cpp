#include "Button.h"

Button::Button() : Object() 
{
	text = nullptr;
}

Button::Button(const Button & other) { }

Button::~Button() { }

bool Button::Start(glm::vec2 screenSize, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, glm::vec4 color)
{
	Object::Start("", material);

	this->position = position;
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1 * size.x, 1 * size.y, 1);
	this->screenSize = screenSize;
	this->size = size;
	this->color = color;

	// Creating model object
	model = new Model();
	if (model == nullptr) return false;

	// Updating quad model
	model->BuildQuadTexture();

	return true;
}

void Button::Stop()
{
	if (text != nullptr)
	{
		text->Stop();
		delete text;
		text = nullptr;
	}

	Object::Stop();
}

bool Button::StartText(std::string fontName, float characterSize)
{
	// Creating text object
	text = new Text();
	if (text == nullptr) return false;
	if (!text->Start(screenSize, fontName, characterSize, position, rotation, scale))
		return false;

	text->CreateText("Default");

	return true;
}

bool Button::isMouseInside()
{
	glm::vec2 mousePosition = fromScreenToWorld(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
	return (mousePosition.x > position.x && mousePosition.x < position.x + size.x &&
		mousePosition.y > position.y && mousePosition.y < position.y + size.y);
}

void Button::Update(GLint deltaT)
{
	switch (state)
	{
	case Hovering:
	case Pressed:
	case Released:
	//	position.x += 1;
		break;
	case Nothing:
		break;
	}

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

void Button::Draw()
{
	// Draws the actual button quad
	Object::Draw();

//	if (text != nullptr)
//		text->Draw();
}

void Button::setShader(GLuint shader)
{
	this->shader = shader;
	
	if (text != nullptr)
		this->text->setShader(shader);
}

void Button::setState(State state) { this->state = state; }

void Button::setSize(glm::vec2 size) { this->size = size; scale.x = size.x; scale.y = size.y; }

void Button::setColor(glm::vec4 color) { this->color = color; }

Button::State Button::getState() { return state; }

glm::vec2 Button::getSize() { return size; }

glm::vec4 Button::getColor() { return color; }
