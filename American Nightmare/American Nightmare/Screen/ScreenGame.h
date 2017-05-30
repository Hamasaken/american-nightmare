#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "Screen.h"
#include "Rendering/DeferredRendering.h"
#include "Rendering/ShadowManager.h"
#include "../Game/Player.h"
#include "../Game/LevelManager.h"
#include "../Game/Particle/ParticleManager.h"
#include "../Game/GUI/GUIManager.h"

#define PAUS_TIMER 300.f

class ScreenGame : public Screen
{
private:
	enum GameState { PAUSED, PAUSING, UNPAUSING, PLAYING };
public:
	ScreenGame();
	ScreenGame(const ScreenGame& other);
	~ScreenGame();

	////////////////////////////////////////////////////////////
	// \brief Loads everything related to the playable game
	// \return Returns false if any object could not be loaded
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager);

	////////////////////////////////////////////////////////////
	// \brief Unloads everything related to this screen 
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Set hardcoded stuff (camera start, ui) & loading map
	////////////////////////////////////////////////////////////
	void SetStartVariables(std::string levelPath, std::string archivePath);

	////////////////////////////////////////////////////////////
	// \brief Update game screen
	////////////////////////////////////////////////////////////
	void Update(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Draw game screen 
	////////////////////////////////////////////////////////////
	void Draw();

	////////////////////////////////////////////////////////////
	// \brief Pausing 
	////////////////////////////////////////////////////////////
	void Pause();

	////////////////////////////////////////////////////////////
	// \brief Update Screen Properties 
	////////////////////////////////////////////////////////////
	void UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos);

private:
	void UpdatePaused(GLint deltaT);
	void UpdatePlaying(GLint deltaT);
	void UpdatePausing(GLint deltaT);
	void UpdateUnpausing(GLint deltaT);

	bool SetupUI();
	bool ResetLevel();
	void DrawShadowMaps();

	Button* background;
	GameState gameState;				//< Current State of the gameloop
	GUIManager* guiManager;				//< Paus Meny
	GUIManager* uiManager;				//< UI
	LevelManager* levelManager;			//< Manager for levels/maps
	DeferredRendering drRendering;		//< Holds framebuffer for deferred rendering
	ShadowManager shadowManager;		//< Manager for shadow maps
};

#endif // !SCREENGAME_H
