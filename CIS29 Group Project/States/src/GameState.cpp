#include "stdafx.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* renderWindow)
	: State(renderWindow)
{
}

GameState::~GameState()
{
}

void GameState::updateKeybinds(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		quitState();
	}
}

void GameState::updateState(const float& deltaTime)
{
	updateKeybinds(deltaTime);

	std::cout << "Running GameState" << std::endl;
}

void GameState::renderState(sf::RenderTarget* renderTarget)
{
}
