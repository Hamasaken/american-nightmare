#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "Screen.h"

class ScreenGame : public Screen
{
public:
	ScreenGame();
	ScreenGame(const ScreenGame& other);
	~ScreenGame();
};

#endif // !SCREENGAME_H
