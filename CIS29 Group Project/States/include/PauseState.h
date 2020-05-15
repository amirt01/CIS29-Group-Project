#pragma once

#include "State.h"
#include "GUI.h"

class PauseState :
	public State {
private:
	// Variables
	sf::RectangleShape background;
	sf::RectangleShape container;
	
	sf::Font font;

	std::map<std::string, gui::Button *> buttons;
	
	unsigned short resumeQuit;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeContainer();
	void initializeFonts();
	void initializeButtons();
public:
	PauseState(sf::RenderWindow * renderWindow, std::stack<State *> * states);
	~PauseState();

	// Update
	void updateButtons();
	void updateInput(unsigned short keyCode);
	void updateState(const float & deltaTime);

	// Render
	const bool isButtonPressed(std::string Button);
	void renderButtons(sf::RenderTarget * renderTarget);
	void renderState(sf::RenderTarget * renderTarget);
};

