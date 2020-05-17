#pragma once

#include "State.h"
#include "PauseState.h"

class GameState :
	public State
{
protected:
	PauseState pauseState;
	std::map<std::string, gui::Button*> buttons;
	void togglePause();

	std::stack<State*>* states;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	// Initializers
	void initializeBackground();
public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~GameState();

	// Update
	void updateGUI();
	void updateInput(unsigned short keyCode);
	void updateState(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};