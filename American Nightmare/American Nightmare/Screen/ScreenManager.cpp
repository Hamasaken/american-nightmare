#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
	// Setting every screen as nullptrs
	screenGame = nullptr;
	screenStart = nullptr;
	screenCutscene = nullptr;
	screenOptions = nullptr;
	screenPosters = nullptr;
}

ScreenManager::ScreenManager(const ScreenManager & other) { }

ScreenManager::~ScreenManager() { }

bool ScreenManager::Start(glm::vec2 screenSize, glm::vec2 screenPosition, HWND hwnd)
{
	// Get parameters
	this->hwnd = hwnd;
	this->screenSize = screenSize;
	this->screenPosition = screenPosition;

	// Setting start screen
	currentState = State(START_STATE);
	prevState = State(START_STATE);

	// Starting sound manager
	soundManager = new SoundManager();
	if (soundManager == nullptr) return false;

	// Trying to initialize start screen
	if (!StartCurrentScreen()) 
		return false;

	return true;
}

void ScreenManager::Stop()
{
	if (screenGame != nullptr) 
	{
		screenGame->Stop();
		delete screenGame;
		screenGame = nullptr;
	}

	if (screenStart != nullptr)
	{
		screenStart->Stop();
		delete screenStart;
		screenStart = nullptr;
	}

	if (screenCutscene != nullptr)
	{
		screenCutscene->Stop();
		delete screenCutscene;
		screenCutscene = nullptr;
	}

	if (screenOptions != nullptr)
	{
		screenOptions->Stop();
		delete screenOptions;
		screenOptions = nullptr;
	}

	if (screenPosters != nullptr)
	{
		screenPosters->Stop();
		delete screenPosters;
		screenPosters = nullptr;
	}

	if (soundManager != nullptr)
	{
		delete soundManager;
		soundManager = nullptr;
	}
}

bool ScreenManager::StartCurrentScreen()
{
	switch (currentState)
	{
	case State::Game: 
		screenGame = new ScreenGame();
		if (screenGame == nullptr) return false;
		if (!screenGame->Start(screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Game Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::StartMeny:
		screenStart = new ScreenStart();
		if (screenStart == nullptr) return false;
		if (!screenStart->Start(screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Start Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::Cutscene:
		screenCutscene = new ScreenCutscene();
		if (screenCutscene == nullptr) return false;
		if (!screenCutscene->Start(screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Cutscene Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::Options:
		screenOptions = new ScreenOptions();
		if (screenOptions == nullptr) return false;
		if (!screenOptions->Start(screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Options Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::Posters:
		screenPosters = new ScreenPosters();
		if (screenPosters == nullptr) return false;
		if (!screenPosters->Start(screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Posters Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	}

	return true;
}

void ScreenManager::StopScreen(State state)
{
	switch (state)
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
	case State::Cutscene:
		if (screenCutscene != nullptr)
		{
			screenCutscene->Stop();
			screenCutscene = nullptr;
		}
		break;
	case State::Options:
		if (screenOptions != nullptr)
		{
			screenOptions->Stop();
			screenOptions = nullptr;
		}
		break;
	case State::Posters:
		if (screenPosters != nullptr)
		{
			screenPosters->Stop();
			screenPosters = nullptr;
		}
		break;
	}
}

bool ScreenManager::goToState(State state)
{
	// Stopping active screen
	StopScreen(prevState);

	// Changing current state
	currentState = state;

	// Starting new screen
	if (!StartCurrentScreen())
		return false;

	return true;
}

void ScreenManager::Update(GLint deltaT)
{
	// Temporary state switching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))		{ goToState(Game); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))	{ goToState(StartMeny); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) { goToState(Options); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F4))	{ goToState(Posters); }
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F5))	{ goToState(Cutscene); }

	prevState = currentState;
	switch (currentState)
	{
	case State::Game: screenGame->Update(deltaT); break;
	case State::StartMeny: screenStart->Update(deltaT); break;
	case State::Cutscene: screenCutscene->Update(deltaT); break;
	case State::Options: screenOptions->Update(deltaT); break;
	case State::Posters: screenPosters->Update(deltaT); break;
	}

	if (prevState != currentState)
		goToState(currentState);
}

void ScreenManager::Draw(SDL_Window* window, glm::vec4 color)
{
	// Clearing the screen to the clear color
	glClearColor(color.r, color.g, color.b, color.a);

	// Cleaning screen & depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (currentState)
	{
	case State::Game: screenGame->Draw(); break;
	case State::StartMeny: screenStart->Draw(); break;
	case State::Cutscene: screenCutscene->Draw(); break;
	case State::Options: screenOptions->Draw(); break;
	case State::Posters: screenPosters->Draw(); break;
	}

	SDL_GL_SwapWindow(window);
}

State ScreenManager::getState()
{
	return State(currentState);
}
