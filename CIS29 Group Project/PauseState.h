#pragma once

#include "State.h"
#include "GUI.h"

class PauseState :
	public State {
private:
	// Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button *> buttons;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeButtons();
public:
	PauseState(sf::RenderWindow * renderWindow, std::stack<State *> * states);
	~PauseState();

	// Update
	void updateInput(unsigned short keyCode);
	void updateButtons();
	void updateState(const float & deltaTime);

	// Render
	void renderButtons(sf::RenderTarget * renderTarget);
	void renderState(sf::RenderTarget * renderTarget);
};

