#include "stdafx.h"
#include "Level.h"

void Level::initializeVariables()
{
	frequency = 3; // seconds
}

void Level::initializeLevel(std::string path)
{
	unsigned short top, middle, bottom;

	std::ifstream fin(path);
	
	if (fin.is_open())
	{
		while (fin >> top >> middle >> bottom)
		{

		}
	}
}

std::pair<short, short> Level::setObsticleStates()
{
	return std::pair<short, short>();
}

bool Level::checkForSpawn()
{
	return false;
}

void Level::updateSpawnClock()
{
	std::cout << spawnClock.getElapsedTime().asSeconds() << std::endl;

	if (spawnClock.getElapsedTime().asSeconds() >= frequency) // ready to spawn
	{
		spawnObsticle(setObsticleStates());
		spawnClock.restart();
	}
}

void Level::spawnObsticle(std::pair<short, short> obsticleStats)
{
	spawnObject(obsticleStats.first, obsticleStats.second);
}

Level::Level(sf::RenderWindow* renderWindow, std::string path, std::stack<State*>* states)
	: GameState(renderWindow, states)
{

}

Level::~Level()
{
}

void Level::updateState(const float& deltaTime)
{
}
