#include "stdafx.h"
#include "FreePlayState.h"

void FreePlayState::initializeVariables()
{
	spawnClock.restart();
	GameClock.restart();
}

bool FreePlayState::checkForSpawn()
{
	//if ()
	return 0;
}

void FreePlayState::updateSpawnClock()
{
	readyToSpawn = spawnClock.getElapsedTime().asSeconds() >= 1;
	std::cout << spawnClock.getElapsedTime().asSeconds() << std::endl;

	if (readyToSpawn)
	{
		spawnObsticle();
		spawnClock.restart();
	}
}

void FreePlayState::spawnObsticle()
{
	std::cout << "OBSTICLE SPAWNED!!!" << std::endl;
	system("PAUSE");
}

FreePlayState::FreePlayState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: GameState(renderWindow, states)
{
	initializeVariables();
}

FreePlayState::~FreePlayState()
{
}

void FreePlayState::updateRNG()
{
	switch (randomDevice() % 3)
	{
	case TOP:
		level = TOP;
		break;
	case MIDDLE:
		level = MIDDLE;
		break;
	case BOTTOM:
		level = BOTTOM;
		break;
	default:
		break;
	}

	switch (randomDevice() % 3)
	{
	case MEDIUM:
		obsticle = MEDIUM;
		break;
	case LARGE:
		obsticle = LARGE;
		break;
	case SMALL:
		obsticle = SMALL;
		break;
	default:
		break;
	}

	std::cout << level << '\t' << obsticle << std::endl;
}

void FreePlayState::updateState(const float& deltaTime)
{
	if (!paused)
	{
		updateRNG();
		// MOVE ENEMY
		// UPDATE ENEMY
		updateSpawnClock();
		//checkForSpawn();
	}
	else
	{
		pauseState.updateState(deltaTime);
		updateGUI();
	}
	std::cout << "Running GameState" << std::endl;
}

