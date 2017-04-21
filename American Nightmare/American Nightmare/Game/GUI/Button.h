#ifndef BUTTON_H
#define BUTTON_H

#include "../Object.h"
#include "Text.h"
#include "SDL_ttf.h"

struct Button : Object
{
public:
	// Different states of the button
	enum State { Nothing, Hovering, Pressed, Released };

	Button();
	Button(const Button& other);
	~Button();

	////////////////////////////////////////////////////////////
	// \brief Starts a button
	// \param position Position of the center position of the button (0, 0 is lower left corner)
	// \param size Size of the button & quad
	// \param color Color of the full quad, default as white
	// \param fontName Name of file containing the font (only .ttf's), can be left as nothing
	// \param characterSize Size of the font
	// \return Returns false if model or font could not be created
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f), std::string fontName = "", float characterSize = 30);

	////////////////////////////////////////////////////////////
	// \brief Checking if mouse pointer is inside button
	////////////////////////////////////////////////////////////
	bool isMouseInside();

	////////////////////////////////////////////////////////////
	// \brief Updates button by checking if mouse is hovering/pressing/releasing
	// \param deltaT The time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	void Update(GLint deltaT);	

	////////////////////////////////////////////////////////////
	// \brief Draws the model and the text on top
	////////////////////////////////////////////////////////////
	void Draw();

	// Set & Get functions
	void setState(State state);
	void setSize(glm::vec2 size);
	void setColor(glm::vec4 color);
	State getState();
	Text* getText();
	glm::vec2 getSize();
	glm::vec4 getColor();

private:
	////////////////////////////////////////////////////////////
	// \brief Updates the vertices into a new quad
	////////////////////////////////////////////////////////////
	void UpdateQuad();

	Text* text;				//< Text object, carries text information and font
	glm::vec2 screenSize;	//< The screensize of the screen
	glm::vec2 size;			//< Size of the button in (width, height)
	glm::vec4 color;		//< Color of the button
	State state;			//< Current state of the button
};

#endif // !BUTTON_H
