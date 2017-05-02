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
	this->state = Nothing;
	this->prevState = Nothing;
	this->pressed = false;

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
	if (!text->Start(screenSize, fontName, "BTN text", characterSize, position, rotation, scale))
		return false;

	return true;
}

bool Button::isMouseInside(glm::vec2 mousePosition)
{
	return (mousePosition.x > position.x - size.x &&
			mousePosition.y > -position.y - size.y &&
			mousePosition.x < position.x + size.x &&
			mousePosition.y < -position.y + size.y);
}

void Button::Update(GLint deltaT, glm::vec2 mousePosition)
{
	if (prevState != state)
	{
		switch (state)
		{
		case Hovering:
			setColor(glm::vec4(1, 1, 1, 0.8f));
			break;
		case Pressed:
			setColor(glm::vec4(1, 1, 1, 0.25f));
			break;
		case Released:
			pressed = true;
			break;
		case Nothing:
			setColor(glm::vec4(1, 1, 1, 1.f));
			break;
		}
		prevState = state;
	}

	// Checking if pressed or not
	if (state == State::Pressed)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			state = isMouseInside(mousePosition) ? State::Released : State::Nothing;
	}
	else
	{
		if (isMouseInside(mousePosition))
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

bool Button::getPressed() { return pressed; }
