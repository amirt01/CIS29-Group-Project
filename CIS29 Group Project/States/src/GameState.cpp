#include "stdafx.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* renderWindow)
	: State(renderWindow)
{
}

GameState::~GameState()
{
}

void GameState::updateState(const float& deltaTime)
{
	std::cout << "Running GameState" << std::endl;
}

void GameState::renderState(sf::RenderTarget* renderTarget)
{
}
