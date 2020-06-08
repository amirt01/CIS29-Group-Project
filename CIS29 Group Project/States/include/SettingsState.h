#pragma once

#include "State.h"
#include "GUI.h"

class SettingsState :
	public State
{
private:
	// Variables
	sf::RectangleShape background;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownMenu*> dropDownMenus;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeGUI();
public:
	SettingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	~SettingsState();

	// Update
	void updateKeyboard(unsigned short keyCode);
	void updateGUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget);
};
