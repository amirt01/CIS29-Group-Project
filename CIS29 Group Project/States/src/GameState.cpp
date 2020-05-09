#include "stdafx.h"
#include "GameState.h"

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow)
	: State(renderWindow)
{
}

GameState::~GameState()
{
}

/* Functions */
// Update
void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		quitState();
	}
}

void GameState::updateState(const float& deltaTime)
{
	updateInput(deltaTime);

	std::cout << "Running GameState" << std::endl;
}

// Render
void GameState::renderState(sf::RenderTarget* renderTarget)
{
}
