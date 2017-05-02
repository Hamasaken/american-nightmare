#include "GUIManager.h"

GUIManager::GUIManager() { }

GUIManager::GUIManager(const GUIManager & other) { }

GUIManager::~GUIManager() { }

bool GUIManager::Start(glm::vec2 screenSize)
{
	this->screenSize = screenSize;

	return true;
}

void GUIManager::Stop()
{
	clearButtons();
	clearTexts();
}

void GUIManager::Update(GLuint deltaT)
{
	// Send in mouse pos
	// --

	for (Button* button : buttons)
		button->Update(deltaT);
}

bool GUIManager::AddButton(glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material)
{
	std::string texturePath = TEXTURE_PATH;

	Button* btn = new Button();
	if (btn == nullptr) return false;
	if (!btn->Start(screenSize, position, size, material, glm::vec4(0.8f, 1.f, 0.8f, 1.f))) return false;
	btn->setShader(shader);

	buttons.push_back(btn);
}

bool GUIManager::AddText(glm::vec3 position, float characterSize, std::string text, std::string fontName)
{
	std::string fontPath = FONT_PATH;

	Text* txt = new Text();
	if (txt == nullptr) return false;
	if (!txt->Start(screenSize, fontPath + fontName, text, characterSize, position)) return false;
	txt->setShader(shader);

	texts.push_back(txt);
}

void GUIManager::setAlpha(float alpha)
{
	for (Button* button : buttons)
		button->setColor(glm::vec4(glm::vec3(button->getColor()), alpha));
	for (Text* text : texts)
		text->setColor(glm::vec4(glm::vec3(text->getColor()), alpha));
}

void GUIManager::setShader(GLuint shader)
{
	this->shader = shader;

	for (Button* button : buttons)
		button->setShader(shader);
	for (Text* text : texts)
		text->setShader(shader);
}

std::vector<Button*> GUIManager::getButtonList()
{
	std::vector<Button*> objects;

	for (Button* button : buttons)
		objects.push_back(button);

	return objects;
}

std::vector<Text*> GUIManager::getTextList()
{
	std::vector<Text*> objects;

	for (Text* text : texts)
		objects.push_back(text);

	return objects;
}

void GUIManager::clearButtons()
{
	for (Button* button : buttons)
	{
		button->Stop();
		delete button;
		button = nullptr;
	}
	buttons.clear();
}

void GUIManager::clearTexts()
{
	for (Text* text : texts)
	{
		text->Stop();
		delete text;
		text = nullptr;
	}

	texts.clear();
}
