#ifndef INPUT_H
#define INPUT_H

// INLCUDES
#include <dinput.h>
#include <cstdint>

class Input
{
public:
	Input();
	Input(const Input& other);
	~Input();

	void Start();
	bool Update();

	void ChangeKey(unsigned int key, bool state);
	bool isKeyPressed(unsigned int key);

private:
	unsigned char m_key[256];
	bool m_pressed;
};


#endif // !INPUT_H
