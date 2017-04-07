#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
	// Setting every screen as nullptrs
	screenGame = nullptr;
	screenStart = nullptr;
}

ScreenManager::ScreenManager(const ScreenManager & other) { }

ScreenManager::~ScreenManager() { }

bool ScreenManager::Start(HWND hwnd, OpenGL * openGL)
{
	// Get parameters
	this->hwnd = hwnd;
	this->openGL = openGL;

	// Setting start screen
	currentState = State(START_STATE);

	// Trying to initialize start screen
	if (!StartCurrentScreen()) 
		return false;

	return true;
}

void ScreenManager::Stop()
{
	// Unloads every screen just to be sure

	// Unload game screen
	if (screenGame != nullptr) 
	{
		screenGame->Stop();
		screenGame = nullptr;
	}

	if (screenStart != nullptr)
	{
		screenStart->Stop();
		screenStart = nullptr;
	}
}

bool ScreenManager::StartCurrentScreen()
{
	switch (currentState)
	{
	case State::Game: 
		screenGame = new ScreenGame();
		if (screenGame == nullptr) return false;
		if (!screenGame->Start(openGL))
		{
			MessageBox(hwnd, L"Could not start Game Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::StartMeny:
		screenStart = new ScreenStart();
		if (screenStart == nullptr) return false;
		if (!screenStart->Start(openGL))
		{
			MessageBox(hwnd, L"Could not start Start Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	}

	return true;
}

void ScreenManager::StopCurrentScreen()
{
	switch (currentState)
	{
	case State::Game: 
		if (screenGame != nullptr) 
		{
			screenGame->Stop();
			screenGame = nullptr;
		}
		break;
	case State::StartMeny:
		if (screenStart != nullptr)
		{
			screenStart->Stop();
			screenStart = nullptr;
		}
		break;
	}
}

bool ScreenManager::goToState(State state)
{
	// Stopping active screen
	StopCurrentScreen();

	// Changing current state
	currentState = state;

	// Starting new screen
	if (!StartCurrentScreen())
		return false;

	return true;
}

void ScreenManager::Update()
{
	// Temporary state switching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))		{ goToState(Game); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))	{ goToState(StartMeny); }
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3))	{ goToState(Options); }
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F4))	{ goToState(Posters); }

	switch (currentState)
	{
	case State::Game: screenGame->Update(); break;
	case State::StartMeny: screenStart->Update(); break;
	}
}

void ScreenManager::Draw()
{
	switch (currentState)
	{
	case State::Game: screenGame->Draw(); break;
	case State::StartMeny: screenStart->Draw(); break;
	}
}

ScreenManager::State ScreenManager::getState()
{
	return State(currentState);
}
