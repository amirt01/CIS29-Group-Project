#include "stdafx.h"
#include "FreePlayState.h"

void FreePlayState::initializeVariables()
{
	spawnClock.restart();
	GameClock.restart();
}

void FreePlayState::updateSpawning()
{
	std::cout << spawnClock.getElapsedTime().asSeconds() << std::endl;

	if (spawnClock.getElapsedTime().asSeconds() >= frequency) // ready to spawn
	{
		spawnObject(static_cast<unsigned short>(randomDevice() % 3),  // random position
					static_cast<unsigned short>(randomDevice() % 3)); // random color
		spawnClock.restart();
	}
}

FreePlayState::FreePlayState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: GameState(renderWindow, states)
{
	initializeVariables();
}

FreePlayState::~FreePlayState()
{
}

void FreePlayState::updateState(const float& deltaTime)
{
	if (player == nullptr) {
		spawnPlayer();
	}

	if (!paused)
	{
		updateSpeed(deltaTime);
		updateBackground(deltaTime);
		updateSpawning();

		if (!objects.empty())
		{
			checkCollision();
			updateObjects(deltaTime);
		}
	}
	else
	{
		pauseState.updateState(deltaTime);
		updateGUI();
	}
}

