#ifndef BUTTON_H
#define BUTTON_H

#include "../Object.h"

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
	// \return Returns false if model could not be created
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f));

	////////////////////////////////////////////////////////////
	// \brief Checking if mouse pointer is inside button
	////////////////////////////////////////////////////////////
	bool isMouseInside();

	////////////////////////////////////////////////////////////
	// \brief Updates button by checking if mouse is hovering/pressing/releasing
	// \param deltaT The time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	void Update(GLint deltaT);	

	// Set & Get functions
	void setState(State state);
	void setSize(glm::vec2 size);
	void setColor(glm::vec4 color);
	State getState();
	glm::vec2 getSize();
	glm::vec4 getColor();

private:
	////////////////////////////////////////////////////////////
	// \brief Updates the vertices into a new quad
	////////////////////////////////////////////////////////////
	void UpdateQuad();

	glm::vec2 screenSize;	//< The screensize of the screen
	glm::vec2 size;		//< Size of the button in (width, height)
	glm::vec4 color;	//< Color of the button
	State state;		//< Current state of the button
};

#endif // !BUTTON_H
