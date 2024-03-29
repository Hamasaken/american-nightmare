#include "Text.h"

Text::Text() { }

Text::Text(const Text & other) { }

Text::~Text() 
{
	Stop();
}

bool Text::Start(glm::vec2 screenSize, std::string fontName, float characterSize, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->startPosition = position;
	this->startPosition.z -= 0.001f;
	this->position = position;
	this->position.z -= 0.001f; // pushing the text a tiny notch to be in front of buttons & bars
	this->rotation = rotation;
	this->scale = scale;
	this->screenSize = screenSize;

	// Creating a empty model class
	model = new Model();
	if (model == nullptr) return false;

	// Setting texture as empty
	texture = -1;

	// Loading font, setting default variables
	if (!LoadFont(fontName, characterSize))
		return false;

	return true;
}

void Text::Stop()
{
	// Deleting model
	if (model != nullptr)
	{
		model->Stop();
		delete model;
		model = nullptr;
	}

	// Deleting texture
	if (texture != -1)
	{
		glDeleteTextures(1, &texture);
		texture = -1;
	}

	// Unload Font
	if (font != nullptr)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}
}

bool Text::LoadFont(std::string fontName, float characterSize)
{
	// Open Font
	font = nullptr;
	font = TTF_OpenFont((fontName).c_str(), characterSize);
	if (font == nullptr)
		return false;

	return true;
}

void Text::CreateText(std::string text, glm::vec4 color)
{
	// Deleting current text if we're modifying
	if (texture != -1) 
	{
		glDeleteTextures(1, &texture);
		model->Stop();
		delete model;
		model = nullptr;
		model = new Model();
	}

	// Saving parameters
	this->text = text;
	this->color = color;

	// Text Color
	SDL_Color clr = { color.r * 255.f, color.g * 255.f, color.b * 255.f, color.a * 255.f };

	// Create Surface
	SDL_Surface* surface;
	surface = TTF_RenderText_Blended(font, text.c_str(), clr);
	scale = glm::vec3(surface->w / screenSize.x, surface->h / screenSize.y, 1.f);

	// Create OpenGL Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

	// Setting some important parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbinding
	glBindTexture(GL_TEXTURE_2D, 0);

	// Deleting surface
	SDL_FreeSurface(surface);

	// Creating quad for this text
	model->BuildQuadTextureBig();
}

void Text::Draw()
{
	Object::Draw();
}

glm::vec3 Text::getStartPosition() { return startPosition; }
std::string Text::getString() { return text; }
GLuint Text::getTexture() const { return texture; }
glm::vec4 Text::getColor() { return color; }
void Text::setString(std::string text) { this->text = text; CreateText(text, color); }
void Text::setColor(glm::vec4 color) { this->color = color; CreateText(text, color); }