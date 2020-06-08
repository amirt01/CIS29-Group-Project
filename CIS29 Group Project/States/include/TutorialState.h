#pragma once

#include "State.h"
#include "GUI.h"

class TutorialState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	// Initializers
	void initializeTextures();
	void initializeFonts();
	void initializeGUI();

public:
	// Constructors/Destructors
	TutorialState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~TutorialState();

	// Update
	void updateMouseButtons(const sf::Mouse::Button& button);
	void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateMouseWheel(const short& mouseDelta);

	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};