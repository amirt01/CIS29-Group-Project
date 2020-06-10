#include "stdafx.h"
#include "Level.h"
#include "ExceptionHandler.h"

unsigned char leftNibble(unsigned char data) { return data >> 4; }
unsigned char rightNibble(unsigned char data) { return data & 0xF; }

void Level::initializeLevel()
{
	unsigned char buffer;

	std::ifstream fin(levelPath);
	try {
		if (!fin.is_open())
			throw exc::LoadFromFileError(levelPath);

		while (fin.read(reinterpret_cast<char*>(&buffer), sizeof(buffer)))
		{
			waves.push(buffer);
		}

		fin.close();
	}
	catch (exc::LoadFromFileError& error)
	{
		std::cout << error.what() << std::endl;
		exit(-1);
	}
}

void Level::updateSpawning()
{
	if (spawnTime >= frequency) // ready to spawn
	{
		if (!waves.empty())
		{
			unsigned short level, color;
			spawnTime = 0;
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
				color = RED;
				break;
			case(0x2): // Middle
				color = YELLOW;
				break;
			case(0x4): // Bottom
				color = ORANGE;
				break;
			default:
				color = -1;
			}
			spawnObject(level, color);
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

void Level::restartState()
{
	GameState::renderState();
	std::queue<unsigned char> empty;
	std::swap(waves, empty);

	initializeLevel();
}

Level::Level(sf::RenderWindow* renderWindow, std::string path, std::stack<State*>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard)
	: GameState(renderWindow, states, textures, fonts, soundBuffers, leaderboard), levelPath(path)
{
	initializeLevel();
	spawnPlayer();
}

Level::~Level()
{
}