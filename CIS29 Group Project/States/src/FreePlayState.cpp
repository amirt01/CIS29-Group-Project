#include "stdafx.h"
#include "FreePlayState.h"

void FreePlayState::updateSpawning()
{
	if (spawnTime >= frequency) // ready to spawn
	{
		spawnTime = 0;
		spawnObject(static_cast<unsigned short>(randomDevice() % 3),  // random position
			static_cast<unsigned short>(randomDevice() % 3)); // random color
	}
}

FreePlayState::FreePlayState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: GameState(renderWindow, states)
{
	spawnPlayer();
}

FreePlayState::~FreePlayState()
{
}