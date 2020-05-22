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
		spawnObsticle(setObsticleStates());
		spawnClock.restart();
	}
}

void FreePlayState::spawnObsticle(std::pair<short, short> obsticleStats)
{
	std::cout << "OBSTICLE SPAWNED!!!" << std::endl;
	std::cout << obsticleStats.first << " at " << obsticleStats.second << std::endl;
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

std::pair<short, short> FreePlayState::setObsticleStates()
{
	short level, obsticle;
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

	return std::make_pair(level, obsticle);
}

void FreePlayState::updateState(const float& deltaTime)
{
	if (!paused)
	{
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

