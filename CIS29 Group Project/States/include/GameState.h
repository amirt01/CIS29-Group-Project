#pragma once

#include "State.h"

class GameState :
	public State
{

public:
	GameState(sf::RenderWindow* renderWindow);
	virtual ~GameState();

	void updateState(const float& deltaTime);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};