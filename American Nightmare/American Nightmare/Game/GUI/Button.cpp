#include "Button.h"

Button::Button() : Object() 
{
	text = nullptr;
}

Button::Button(const Button & other) { }

Button::~Button() 
{

}

bool Button::Start(glm::vec2 screenSize, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, const MeshManager::Mesh* mesh)
{
	if (!Object::Start(mesh, material))
		return false;

	this->startPosition = position;
	this->position = position;
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1 * size.x, 1 * size.y, 1);
	this->screenSize = screenSize;
	this->size = size;
	this->state = Nothing;
	this->prevState = Nothing;
	this->pressed = false;
	this->alpha = BTN_ALPHA_NORMAL;

	return true;
}

void Button::Stop()
{
	Object::~Object();

	if (text != nullptr)
	{
		text->Stop();
		delete text;
		text = nullptr;
	}
}

bool Button::StartText(std::string str, std::string fontName, float characterSize, glm::vec4 textColor)
{
	// Creating text object
	text = new Text();
	if (text == nullptr) return false;
	if (!text->Start(screenSize, fontName, characterSize, position, rotation, scale))
		return false;

	// Adding text to it
	text->CreateText(str, textColor);

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
			setAlpha(BTN_ALPHA_HOVER);
			break;
		case Pressed:
			setAlpha(BTN_ALPHA_PRESSED);
			break;
		case Released:
			pressed = true;
			break;
		case Nothing:
			setAlpha(BTN_ALPHA_NORMAL);
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
	Object::Draw();
}

void Button::setShader(GLuint shader)
{
	this->shader = shader;
	
	if (text != nullptr)
		this->text->setShader(shader);
}

void Button::setPosition(glm::vec3 position)
{
	this->position = position;
	if (text != nullptr) 
		text->setPosition(glm::vec3(position.x, position.y, position.z - 0.001f));
}

glm::vec3 Button::getStartPosition() { return startPosition; }
void Button::setState(State state) { this->state = state; }
void Button::setSize(glm::vec2 size) { this->size = size; scale.x = size.x; scale.y = size.y; }
void Button::setAlpha(float alpha) { this->alpha = alpha; }
void Button::setPressed(bool pressed) { this->pressed = pressed; }
Text * Button::getText() { return text; }
Button::State Button::getState() { return state; }
glm::vec2 Button::getSize() { return size; }
float Button::getAlpha() { return alpha; }
bool Button::getPressed() { return pressed; }
