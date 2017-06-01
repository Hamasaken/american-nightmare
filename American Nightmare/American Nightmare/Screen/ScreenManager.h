#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "ScreenGame.h"
#include "ScreenStart.h"
#include "ScreenPosters.h"
#include "ScreenOptions.h"
#include "../SoundManager.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <Windows.h>

#define START_STATE 1 // 0 = Game, 1 = Startmeny

class ScreenManager
{
public:
	State currentState;
	State prevState;

	ScreenManager();
	ScreenManager(const ScreenManager& other);
	~ScreenManager();

	////////////////////////////////////////////////////////////
	// \brief Saves openGL ptr and starts the start screen
	// \param screenSize The size of the screen in pixels
	// \param screenPosition The position of the screen in pixels, upper left corner
	// \param hwnd The window properties
	////////////////////////////////////////////////////////////
	bool Start(SDL_Window* window, glm::vec2 screenSize, glm::vec2 screenPosition, HWND hwnd);

	////////////////////////////////////////////////////////////
	// \brief Unloads every screen
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Starts the screen with the current state
	// \return Returns false if the screen could not be started
	////////////////////////////////////////////////////////////
	bool StartCurrentScreen();

	////////////////////////////////////////////////////////////
	// \brief Unloads a specific screen
	////////////////////////////////////////////////////////////
	void StopScreen(State state);

	////////////////////////////////////////////////////////////
	// \brief Will switch current state and it will also run the 
	//	stop function for the current state and unload everything
	//	it will do nothing if we are already in same state
	// \return Returns true if the Start function of the new state worked
	//	otherwise it returns false
	////////////////////////////////////////////////////////////
	bool goToState(State state);

	////////////////////////////////////////////////////////////
	// \brief Pause the game if we're in the game
	////////////////////////////////////////////////////////////
	void FocusLost();

	////////////////////////////////////////////////////////////
	// \brief Updates the active screen
	////////////////////////////////////////////////////////////
	void Update(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Draws the active screen
	////////////////////////////////////////////////////////////
	void Draw(SDL_Window* window, glm::vec4 color);

	////////////////////////////////////////////////////////////
	// \brief Updates the screenposition and screensize of everything
	////////////////////////////////////////////////////////////
	void UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos);

	////////////////////////////////////////////////////////////
	// \brief Returns the current screen
	////////////////////////////////////////////////////////////
	State getState();
private:
	SDL_Window* window;				//< Pointer to current window
	glm::vec2 screenSize;			//< The current screenSize
	glm::vec2 screenPosition;		//< The current screenPosition
	HWND hwnd;						//< Saving the HWND for error msg boxes output
	SoundManager* soundManager;		//< Manages the sfx and music
	ScreenGame* screenGame;			//< The game screen
	ScreenStart* screenStart;		//< The start meny screen
	ScreenOptions* screenOptions;	//< The screen for the options
	ScreenPosters* screenPosters;	//< The screen for posters
};

#endif // !SCREENMANAGER_H
