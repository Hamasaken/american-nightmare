#ifndef BUTTON_H
#define BUTTON_H

#include "../Object.h"

struct Button : Object
{
public:
	Button();
	Button(const Button& other);
	~Button();

	void Update(GLint deltaT);

private:

};

#endif // !BUTTON_H
