#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
	Screen() { }
	Screen(const Screen& other) { }
	virtual ~Screen() = 0;
};

#endif // !SCREEN_H
