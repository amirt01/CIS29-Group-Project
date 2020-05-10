#pragma once

#include "State.h"

class MainMenuState :
	public State
{
private:
	sf::RectangleShape background;

public:
	// Constructors/Destructors
	MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~MainMenuState();

	// Update
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};