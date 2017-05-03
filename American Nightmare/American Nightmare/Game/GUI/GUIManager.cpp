#include "GUIManager.h"

GUIManager::GUIManager() { }

GUIManager::GUIManager(const GUIManager & other) { }

GUIManager::~GUIManager() { }

bool GUIManager::Start(glm::vec2 screenSize, glm::vec2 screenPosition)
{
	this->screenSize = screenSize;
	this->screenPosition = screenPosition;

	return true;
}

void GUIManager::Stop()
{
	clearButtons();
	clearTexts();
}

void GUIManager::Update(GLuint deltaT)
{
	glm::vec2 mousePosition = fromScreenToWorld(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), screenSize, screenPosition);

	for (std::pair<Button*, Action> button : buttons)
		button.first->Update(deltaT, mousePosition);
}

bool GUIManager::AddButton(Action action, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material)
{
	std::string texturePath = TEXTURE_PATH;

	Button* btn = new Button();
	if (btn == nullptr) return false;
	if (!btn->Start(screenSize, position, size, material, glm::vec4(0.8f, 1.f, 0.8f, 1.f))) return false;
	btn->setShader(shader);

	buttons.push_back(std::make_pair(btn, action));
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
	for (std::pair<Button*, Action> button : buttons)
		button.first->setColor(glm::vec4(glm::vec3(button.first->getColor()), alpha));
	for (Text* text : texts)
		text->setColor(glm::vec4(glm::vec3(text->getColor()), alpha));
}

void GUIManager::setShader(GLuint shader)
{
	this->shader = shader;

	for (std::pair<Button*, Action> button : buttons)
		button.first->setShader(shader);
	for (Text* text : texts)
		text->setShader(shader);
}

std::vector<std::pair<Button*, GUIManager::Action>>* GUIManager::getButtonList()
{
	return &buttons;
}

std::vector<Text*>* GUIManager::getTextList()
{
	return &texts;
}

void GUIManager::clearButtons()
{
	for (std::pair<Button*, Action> button : buttons)
	{
		button.first->Stop();
		delete button.first;
		button.first = nullptr;
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
