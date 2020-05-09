#pragma once

#include "State.h"

class GameState :
	public State
{
public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow);
	virtual ~GameState();

	// Update
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};