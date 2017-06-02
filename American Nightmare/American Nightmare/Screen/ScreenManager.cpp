#include "ScreenManager.h"

std::vector<uint16_t> unlockedPosters;

ScreenManager::ScreenManager()
{
	// Setting every screen as nullptrs
	screenGame = nullptr;
	screenStart = nullptr;
	screenOptions = nullptr;
	screenPosters = nullptr;
}

ScreenManager::ScreenManager(const ScreenManager & other) { }

ScreenManager::~ScreenManager() { }

bool ScreenManager::Start(SDL_Window* window, glm::vec2 screenSize, glm::vec2 screenPosition, HWND hwnd)
{
	// Get parameters
	this->hwnd = hwnd;
	this->screenSize = screenSize;
	this->screenPosition = screenPosition;
	this->window = window;

	// Checking to see how many unlocked posters we have
	unlockedPosters.resize(10);
	ifstream in("Data/savedata.fu", ios::binary);
	if (in.is_open())
		in.read(reinterpret_cast<char*>(unlockedPosters.data()), sizeof(uint16_t) * 10);
	in.close();

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
		if (!screenGame->Start(window, screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Game Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::StartMeny:
		screenStart = new ScreenStart();
		if (screenStart == nullptr) return false;
		if (!screenStart->Start(window, screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Start Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::Options:
		screenOptions = new ScreenOptions();
		if (screenOptions == nullptr) return false;
		if (!screenOptions->Start(window, screenSize, screenPosition, &currentState, soundManager))
		{
			MessageBox(hwnd, L"Could not start Options Screen class.", L"Woops", MB_OKCANCEL);
			return false;
		}
		break;
	case State::Posters:
		screenPosters = new ScreenPosters();
		if (screenPosters == nullptr) return false;
		if (!screenPosters->Start(window, screenSize, screenPosition, &currentState, soundManager))
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
			delete screenGame;
			screenGame = nullptr;
		}
		break;
	case State::StartMeny:
		if (screenStart != nullptr)
		{
			screenStart->Stop();
			delete screenStart;
			screenStart = nullptr;
		}
		break;
	case State::Options:
		if (screenOptions != nullptr)
		{
			screenOptions->Stop();
			delete screenOptions;
			screenOptions = nullptr;
		}
		break;
	case State::Posters:
		if (screenPosters != nullptr)
		{
			screenPosters->Stop();
			delete screenPosters;
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

void ScreenManager::FocusLost()
{
	if (currentState == Game)
		screenGame->Pause();
}

void ScreenManager::Update(GLint deltaT)
{
	if(sf::Joystick::isConnected(0))
		sf::Joystick::update();
	
	prevState = currentState;
	switch (currentState)
	{
		case State::Game: screenGame->Update(deltaT); break;
		case State::StartMeny: screenStart->Update(deltaT); break;
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
		case State::Options: screenOptions->Draw(); break;
		case State::Posters: screenPosters->Draw(); break;
	}

	SDL_GL_SwapWindow(window);
}

void ScreenManager::UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos)
{
	this->screenSize = screenSize;
	this->screenPosition = screenPos;

	switch (currentState)
	{
		case State::Game: screenGame->UpdateScreenProperties(screenSize, screenPos); break;
		case State::StartMeny: screenStart->UpdateScreenProperties(screenSize, screenPos); break;
		case State::Options: screenOptions->UpdateScreenProperties(screenSize, screenPos); break;
		case State::Posters: screenPosters->UpdateScreenProperties(screenSize, screenPos); break;
	}
}

State ScreenManager::getState()
{
	return State(currentState);
}
