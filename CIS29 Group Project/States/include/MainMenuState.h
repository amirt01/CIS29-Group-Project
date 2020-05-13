#pragma once

#include "State.h"
#include "GUI.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgrounTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeButtons();

public:
	// Constructors/Destructors
	MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~MainMenuState();

	// Update
	void updateInput();
	void updateButtons();
	void updateState();

	// Render
	void renderButtons(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};