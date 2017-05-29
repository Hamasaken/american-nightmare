#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "Button.h"
#include "Text.h"
#include "Bar.h"

#define GUI_SPEED 0.15f

class GUIManager
{
public:
	enum Action {	OK, CANCEL,									// Simple stuff
					PLAY, PAUSE,								// For In-game
					STARTMENY, OPTIONS, POSTERS, EXIT,			// Switching states
					OPTION_SHADOWS, OPTION_MUTE,				// Option meny
					OPTION_REBIND, OPTION_QUALITY, OPTION_RESET
	};

public:
	GUIManager();
	GUIManager(const GUIManager& other);
	~GUIManager();

	bool Start(glm::vec2 screenSize, glm::vec2 screenPosition);
	void Stop();

	void Update(GLuint deltaT);

	bool AddButton(Action action, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, const MeshManager::Mesh* mesh, std::string text = "", std::string fontName = "", float characterSize = 10.f, glm::vec4 color = glm::vec4(1, 1, 1, 1));
	bool AddBar(float & value, float maxValue, glm::vec3 position, glm::vec2 size, const MaterialManager::Material * material, const MeshManager::Mesh * mesh);
	bool AddText(glm::vec3 position, float characterSize, std::string text, std::string fontName);

	void setInstantCenter(glm::vec2 center);
	void setCenter(glm::vec2 center);
	void setShader(GLuint shader);
	void setAlpha(float alpha);
	void setScreenPosition(glm::vec2 screenPosition);
	void setScreenSize(glm::vec2 screenSize);

	Button* getButton(int id);
	Bar * getBar(int id);

	std::vector<std::pair<Button*, Action>>* getButtonList();
	std::vector<Text*>* getTextList();
	std::vector<Bar*>* getBarList();

private:

	void clearBars();
	void clearButtons();
	void clearTexts();

	glm::vec2 currentCenter;
	glm::vec2 targetCenter;
	glm::vec2 screenSize;
	glm::vec2 screenPosition;
	GLuint shader;
	std::vector<std::pair<Button*, Action>> buttons;
	std::vector<Text*> texts;
	std::vector<Bar*> bars;
};

#endif // !GUIMANAGER_H
