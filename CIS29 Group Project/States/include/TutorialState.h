#pragma once
#pragma once

#include "State.h"
#include "GUI.h"

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
	void updateInput(unsigned short keyCode);
	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};