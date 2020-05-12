#pragma once

#include "State.h"
#include "Button.h"

class SettingsState :
	public State
{
private:
	// Variables
	sf::Texture backgrounTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;
	// Functions
	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeButtons();
public:
	SettingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	~SettingsState();

	// Update
	void updateInput();
	void updateButtons();
	void updateState();

	// Render
	void renderButtons(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};

