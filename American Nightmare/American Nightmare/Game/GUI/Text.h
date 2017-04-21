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

	////////////////////////////////////////////////////////////
	// \brief Starts a new instance of a text
	// \param screenSize The screen size
	// \param fontName The name of the font file (path needed)
	// \param characterSize The size of each character of font
	// \optional position Position of this text, (0, 0, 0) is upper left corner
	// \optional rotation The rotation of the final texture of the text in degrees
	// \optional scale The scale of the final texture of the text
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, std::string fontName, float characterSize, 
		glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 rotation = glm::vec3(0.f,0.f,0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
	
	////////////////////////////////////////////////////////////
	// \brief Unloads everything
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Initializes a version of the text
	// \param text The string of text to be displayed
	// \param color The text color (white if left empty)
	////////////////////////////////////////////////////////////
	void CreateText(std::string text, glm::vec4 color = glm::vec4(1, 1, 1, 1));

	////////////////////////////////////////////////////////////
	// \brief Draws the texture of the text
	////////////////////////////////////////////////////////////
	void Draw();

	// Set & Get functions
	std::string getString();
	glm::vec2 getSize();
	glm::vec4 getColor();
	void setString(std::string text);
	void setColor(glm::vec4 color);

private:

	////////////////////////////////////////////////////////////
	// \brief Loads a font from file
	// \param fontName The name of the file 
	// \param characterSize The size of each letter
	////////////////////////////////////////////////////////////
	bool LoadFont(std::string fontName, float characterSize);

	TTF_Font* font;			//< The font of this text
	std::string text;		//< The string of text to be displayed
	glm::vec2 size;			//< The texture dimension of the full text, can't be changed
	glm::vec4 color;		//< Text color
	glm::vec2 screenSize;	//< The overall screen size
};

#endif // !BUTTON_H
