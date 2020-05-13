#pragma once

#include "State.h"
#include "GUI.h"

class SettingsState :
	public State
{
private:
	// Variables
	sf::Texture backgrounTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeButtons();
public:
	SettingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	~SettingsState();

	// Update
	void updateInput(unsigned short keyCode);
	void updateButtons();
	void updateState(const float& deltaTime);

	// Render
	void renderButtons(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget);
};

