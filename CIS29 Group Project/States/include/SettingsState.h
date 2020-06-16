#pragma once

#include "State.h"
#include "DropDownMenu.h"
#include "GraphicsSettings.h"

class SettingsState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	std::map<std::string, std::unique_ptr<gui::DropDownMenu>> dropDownMenus;

	GraphicsSettings* graphicsSettings;

	// Initializers
	void initializeGUI();
	void resetGUI();

public:
	// Constructors/Destructors
	SettingsState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		GraphicsSettings* graphicsSettings);
	virtual ~SettingsState();

	// Update
	void updateMouseButtons(const sf::Mouse::Button& button);
	void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateMouseWheel(const short& mouseDelta);

	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget);
	void renderState(std::shared_ptr<sf::RenderTarget> renderTarget);
};