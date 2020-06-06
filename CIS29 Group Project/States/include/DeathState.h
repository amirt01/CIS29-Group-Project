#pragma once

#include "State.h"
#include "GUI.h"

class DeathState : public State
{
private:
	// Variables
	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	sf::Text text;
	sf::Text score;

	unsigned short resumeQuit;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeContainer();
	void initializeFonts();
	void initializeGUI(const float& s);
public:
	DeathState(sf::RenderWindow* renderWindow, std::stack<State*>* states, float s);
	~DeathState();

	// Update
	void updateGUI();
	void updateMouseWheel(short mouseDelta);
	void updateKeyboard(unsigned short keyCode);
	void updateState(const float& deltaTime);

	// Render
	const bool isButtonPressed(std::string Button);
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget);
};