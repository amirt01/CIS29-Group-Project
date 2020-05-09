#pragma once

#include "State.h"

class GameState :
	public State
{
public:
	GameState(sf::RenderWindow* renderWindow);
	virtual ~GameState();

	// Update
	void updateKeybinds(const float& deltaTime);
	void updateState(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};