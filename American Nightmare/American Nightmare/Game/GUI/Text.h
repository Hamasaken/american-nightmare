#ifndef TEXT_H
#define TEXT_H

#include "../Object.h"
#include "SDL_ttf.h"

struct Text : Object
{
public:
	Text();
	Text(const Text& other);
	~Text();

	bool Start(glm::vec2 screenSize, std::string fontName, float characterSize, glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 rotation = glm::vec3(0.f,0.f,0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
	void Stop();

	bool LoadFont(std::string fontName, float characterSize);
	void CreateText(std::string text, glm::vec4 color = glm::vec4(1, 1, 1, 1));
	void Draw();

	std::string getString();
	glm::vec2 getSize();
	glm::vec4 getColor();

	void setString(std::string text);
	void setColor(glm::vec4 color);

private:
	TTF_Font* font;
	std::string text;
	glm::vec2 size;
	glm::vec4 color;
	glm::vec2 screenSize;
};

#endif // !BUTTON_H
