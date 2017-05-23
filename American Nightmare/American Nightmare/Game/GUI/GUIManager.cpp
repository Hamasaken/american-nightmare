#include "GUIManager.h"

GUIManager::GUIManager() { }

GUIManager::GUIManager(const GUIManager & other) { }

GUIManager::~GUIManager() { }

bool GUIManager::Start(glm::vec2 screenSize, glm::vec2 screenPosition)
{
	this->screenSize = screenSize;
	this->screenPosition = screenPosition;
	this->targetCenter = glm::vec2(0, 0);
	this->currentCenter = glm::vec2(0, 0);

	return true;
}

void GUIManager::Stop()
{
	clearBars();
	clearButtons();
	clearTexts();
}

void GUIManager::Update(GLuint deltaT)
{
	// Update center position
	if (currentCenter != targetCenter)
	{
		currentCenter += (targetCenter - currentCenter) * GUI_SPEED;
		if (abs(currentCenter.x - targetCenter.x) < 0.001f &&
			abs(currentCenter.y - targetCenter.y) < 0.001f) currentCenter = targetCenter;

		for (std::pair<Button*, Action> button : buttons)
			button.first->setPosition(button.first->getStartPosition() - glm::vec3(currentCenter, 0));
		for (Text* text : texts)
			text->setPosition(text->getStartPosition() - glm::vec3(currentCenter, 0));
		for (Bar* bar : bars)
			bar->setPosition(bar->getStartPosition() - glm::vec3(currentCenter, 0));
	}

	glm::vec2 mousePosition = fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), screenSize, screenPosition);

	for (std::pair<Button*, Action> button : buttons)
		button.first->Update(deltaT, mousePosition);
	for (Bar* bar : bars)
		bar->Update(deltaT);
}

bool GUIManager::AddButton(Action action, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, const MeshManager::Mesh* mesh, std::string text, std::string fontName, float characterSize, glm::vec4 textColor)
{
	Button* btn = new Button();
	if (btn == nullptr) return false;
	if (!btn->Start(screenSize, position, size, material, mesh)) return false;

	// Adding optional text on button
	if (!text.empty())
	{
		if (!btn->StartText(text, fontName, characterSize, textColor)) 
			return false;

	}

	btn->setShader(shader);
	buttons.push_back(std::make_pair(btn, action));
}

bool GUIManager::AddBar(float &value, float maxValue, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, const MeshManager::Mesh* mesh)
{
	Bar* bar = new Bar();
	if (bar == nullptr) return false;
	if (!bar->Start(value, maxValue, position, size, material, mesh)) return false;

	bar->setShader(shader);
	bars.push_back(bar);
}

bool GUIManager::AddText(glm::vec3 position, float characterSize, std::string text, std::string fontName)
{
	Text* txt = new Text();
	if (txt == nullptr) return false;
	if (!txt->Start(screenSize, fontName, characterSize, position)) return false;
	txt->setShader(shader);

	txt->CreateText(text);

	texts.push_back(txt);
}

void GUIManager::setAlpha(float alpha)
{
	for (std::pair<Button*, Action> button : buttons)
		button.first->setAlpha(alpha);
	for (Text* text : texts)
		text->setColor(glm::vec4(glm::vec3(text->getColor().x * alpha, text->getColor().y * alpha, text->getColor().z * alpha), alpha));
	for (Bar* bar : bars)
		bar->setAlpha(alpha);
}

void GUIManager::setScreenPosition(glm::vec2 screenPosition) { this->screenPosition = screenPosition; }

void GUIManager::setScreenSize(glm::vec2 screenSize) { this->screenSize = screenSize; }

Button * GUIManager::getButton(int id)
{
	return buttons[id].first;
}

Bar * GUIManager::getBar(int id)
{
	return bars[id];
}

void GUIManager::setCenter(glm::vec2 center)
{
	this->targetCenter = center;
}

void GUIManager::setInstantCenter(glm::vec2 center)
{
	this->targetCenter = center;
	this->currentCenter = center;

	for (std::pair<Button*, Action> button : buttons)
		button.first->setPosition(button.first->getStartPosition() - glm::vec3(currentCenter, 0));
	for (Text* text : texts)
		text->setPosition(text->getStartPosition() - glm::vec3(currentCenter, 0));
	for (Bar* bar : bars)
		bar->setPosition(bar->getStartPosition() - glm::vec3(currentCenter, 0));
}

void GUIManager::setShader(GLuint shader)
{
	this->shader = shader;

	for (std::pair<Button*, Action> button : buttons)
		button.first->setShader(shader);
	for (Text* text : texts)
		text->setShader(shader);
	for (Bar* bar : bars)
		bar->setShader(shader);
}

std::vector<std::pair<Button*, GUIManager::Action>>* GUIManager::getButtonList()
{
	return &buttons;
}

std::vector<Text*>* GUIManager::getTextList()
{
	return &texts;
}

std::vector<Bar*>* GUIManager::getBarList()
{
	return &bars;
}

void GUIManager::clearBars()
{
	for (Bar* bar : bars)
	{
		bar->Stop();
		delete bar;
		bar = nullptr;
	}
	bars.clear();
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
