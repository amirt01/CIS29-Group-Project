#pragma once

#include "State.h"
#include "Button.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgrounTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeButtons();

public:
	// Constructors/Destructors
	MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~MainMenuState();

	// Update
	void updateInput(const float& deltaTime);
	void updateButtons();
	void updateState(const float& deltaTime);

	// Render
	void renderButtons(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};