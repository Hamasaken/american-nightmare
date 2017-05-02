#ifndef BUTTON_H
#define BUTTON_H

#include "../Object.h"
#include "Text.h"

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
	// \param position Position of the center position of the button
	// \param size Size of the button & quad
	// \param material The material of this button (no path needed)
	// \param color Color of the full quad, default as white
	// \return Returns false if model or font could not be created
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f));

	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Starts text on the button
	// \param fontName Full path to the font file
	// \param characterSize The size of each character
	////////////////////////////////////////////////////////////
	bool StartText(std::string fontName, float characterSize);

	////////////////////////////////////////////////////////////
	// \brief Checking if mouse pointer is inside button
	////////////////////////////////////////////////////////////
	bool isMouseInside(glm::vec2 mousePosition);

	////////////////////////////////////////////////////////////
	// \brief Updates button by checking if mouse is hovering/pressing/releasing
	// \param deltaT The time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	void Update(GLint deltaT, glm::vec2 mousePosition);

	////////////////////////////////////////////////////////////
	// \brief Draws the model and the text on top
	////////////////////////////////////////////////////////////
	void Draw();

	// Overdrivven set shader to also set text shader
	void setShader(GLuint shader);

	// Set & Get functions
	void setState(State state);
	void setSize(glm::vec2 size);
	void setColor(glm::vec4 color);
	State getState();
	glm::vec2 getSize();
	glm::vec4 getColor();
	bool getPressed();
	void setPressed(bool pressed);

private:
	bool pressed;			//< If the button have been pressed or not
	Text* text;				//< Optional text object
	glm::vec2 screenSize;	//< The screensize of the screen
	glm::vec2 size;			//< Size of the button in (width, height)
	glm::vec4 color;		//< Color of the button
	State state;			//< Current state of the button
	State prevState;		//< The previous state of the button (for optimazition)
};

#endif // !BUTTON_H
