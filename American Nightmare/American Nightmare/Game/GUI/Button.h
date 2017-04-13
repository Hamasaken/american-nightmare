#ifndef BUTTON_H
#define BUTTON_H

#include "../Object.h"

struct Button : Object
{
public:
	enum State { Nothing, Hovering, Pressed, Released };

	Button();
	Button(const Button& other);
	~Button();

	void Start(glm::vec2 position, glm::vec2 size);

	void Update(GLint deltaT);	

	State getState();
	void setState(State state);

private:
	State state;
};

#endif // !BUTTON_H
