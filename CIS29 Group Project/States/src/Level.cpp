#include "stdafx.h"
#include "Level.h"

unsigned char leftNibble(unsigned char data) { return data >> 4; }
unsigned char rightNibble(unsigned char data) { return data & 0xF; }

void Level::initializeVariables()
{
	spawnClock.restart();
}

void Level::initializeLevel(std::string path)
{
	unsigned char buffer;

	std::ifstream fin(path);
	try {
		if(!fin.is_open())
			throw std::invalid_argument(path);
	}
	catch (std::invalid_argument& error)
	{
		exit(-1);
	}

	while (fin.read(reinterpret_cast<char*>(&buffer), sizeof(buffer)))
	{
		waves.push(buffer);
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
			unsigned short level, color;
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

			switch (leftNibble(waves.front()))
			{
			case(0x1): // Top
				color = Red;
				break;
			case(0x2): // Middle
				color = Yellow;
				break;
			case(0x4): // Bottom
				color = Orange;
				break;
			default:
				color = -1;
			}
			spawnObsticle(level, color);
			spawnClock.restart();
			waves.pop();
		}
		else if (objects.empty())
		{
			// MAKE NICER LATER
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
	if (player == nullptr) {
		spawnPlayer();
	}

	if (!paused)
	{
		updateSpawnClock();

		if (!objects.empty()) {
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
