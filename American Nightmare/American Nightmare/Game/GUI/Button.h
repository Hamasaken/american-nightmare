#ifndef BUTTON_H
#define BUTTON_H

#include "../Object.h"
#include "Text.h"

#define BTN_ALPHA_HOVER 0.8f
#define BTN_ALPHA_PRESSED 0.25f
#define BTN_ALPHA_NORMAL 1.f

struct Button : public Object
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
	// \param mesh The mesh of this button (leave as nullptr for normal quad)
	// \return Returns false if model or font could not be created
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, const MeshManager::Mesh* mesh);
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Starts text on the button
	// \param str The string of the button text
	// \param fontName Path to the .ttf file
	// \optional characterSize The size of each character (defaults as 20.f)
	// \optional textColor The color of the full text (defaults as WHITE) 
	////////////////////////////////////////////////////////////
	bool StartText(std::string str, std::string fontName, float characterSize = 20.f, glm::vec4 color = glm::vec4(1, 1, 1, 1));

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

	// Overdrivven setfunctions
	void setShader(GLuint shader);
	void setPosition(glm::vec3 position);
	glm::vec3 getStartPosition();

	// Set & Get functions
	void setState(State state);
	void setSize(glm::vec2 size);
	void setAlpha(float alpha);
	void setPressed(bool pressed);
	Text* getText();
	State getState();
	glm::vec2 getSize();
	float getAlpha();
	bool getPressed();

private:
	glm::vec3 startPosition;//< The starting position of this button
	bool pressed;			//< If the button have been pressed or not
	Text* text;				//< Optional text object
	glm::vec2 screenSize;	//< The screensize of the screen
	glm::vec2 size;			//< Size of the button in (width, height)
	float alpha;			//< The alpha of the button
	State state;			//< Current state of the button
	State prevState;		//< The previous state of the button (for optimazition)
};

#endif // !BUTTON_H
