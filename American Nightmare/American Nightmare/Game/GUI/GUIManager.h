#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "Button.h"
#include "Text.h"

class GUIManager
{
public:
	GUIManager();
	GUIManager(const GUIManager& other);
	~GUIManager();

	bool Start(glm::vec2 screenSize);
	void Stop();

	bool AddButton(glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material);
	bool AddText(glm::vec3 position, float characterSize, std::string text, std::string fontName);

	void setShader(GLuint shader);
	void setAlpha(float alpha);

	std::vector<Object*> getObjectList();

private:

	void clearButtons();
	void clearTexts();

	glm::vec2 screenSize;
	GLuint shader;
	std::vector<Button*> buttons;
	std::vector<Text*> texts;
};

#endif // !GUIMANAGER_H
