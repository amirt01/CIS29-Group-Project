#include "stdafx.h"
#include "Level.h"

unsigned char leftNibble(unsigned char data)
{
	return data >> 4;
}

unsigned char rightNibble(unsigned char data)
{
	return data & 0xF;
}

void Level::initializeVariables()
{
	spawnClock.restart();
}

void Level::initializeLevel(std::string path)
{
	unsigned char buffer;

	std::ifstream fin(path);
	
	if (fin.is_open())
	{
		while (fin.read(reinterpret_cast<char*>(&buffer), sizeof(buffer)))
		{
			waves.push(buffer);
		}
	}
	else
	{
		throw "ERROR::LEVEL::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
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
		if (!waves.empty())
		{
			unsigned short level;
			switch (rightNibble(waves.front()))
			{
			case(0x1): // Top
				level = TOP;
				break;
			case(0x2): // Middle
				level = MIDDLE;
				break;
			case(0x4): // Bottom
				level = BOTTOM;
				break;
			default:
				level = -1;
			}
			spawnObsticle(level, 0);
			spawnClock.restart();
			waves.pop();
		}
		else if (objects.empty())
		{
			std::cout << "YOU WIN!!!" << std::endl;
			system("PAUSE");
			quitState();
		}
	}
}

void Level::spawnObsticle(unsigned short level, unsigned short type)
{
	spawnObject(level, type);
}

Level::Level(sf::RenderWindow* renderWindow, std::string path, std::stack<State*>* states)
	: GameState(renderWindow, states)
{
	initializeLevel(path);
	initializeVariables();
}

Level::~Level()
{
}

void Level::updateState(const float& deltaTime)
{
	if (players == nullptr) {
		spawnPlayer();
	}

	if (!paused)
	{
		updateSpawnClock();

		if (!objects.empty())
			updateObjects(deltaTime);
	}
	else
	{
		pauseState.updateState(deltaTime);
		updateGUI();
	}
}
