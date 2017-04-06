#include "Input.h"

Input::Input() { }

Input::Input(const Input&) { }

Input::~Input() { }

void Input::Start()
{
	// Initialize all the keys to being released and not pressed.
	for (int i = 0; i < 256; i++)
	{
		m_key[i] = false;
	}
}

bool Input::Update()
{
	// ESCAPE BUTTON
	if (isKeyPressed(VK_ESCAPE))
	{
		return false;
	}
	return true;
}

void Input::ChangeKey(unsigned int key, bool state)
{
	m_key[key] = state;
}

bool Input::isKeyPressed(unsigned int key)
{
	return (m_key[key]);
}