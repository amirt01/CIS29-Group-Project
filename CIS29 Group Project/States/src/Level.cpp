#include "stdafx.h"
#include "Level.h"
#include "LoadFromFileError.h"

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
		int i = 0;
		do
		{
			if (!waves.empty())
			{
				Levels level;
				Color color;
				spawnTime = 0;
				switch (rightNibble(waves.front()))
				{
				case(0x1): // Top
					level = Levels::TOP;
					break;
				case(0x2): // Middle
					level = Levels::MIDDLE;
					break;
				case(0x4): // Bottom
					level = Levels::BOTTOM;
					break;
				default:
					level = Levels::MIDDLE;
				}

				switch (leftNibble(waves.front()))
				{
				case(0x1): // Top
					color = Color::RED;
					break;
				case(0x2): // Middle
					color = Color::YELLOW;
					break;
				case(0x4): // Bottom
					color = Color::ORANGE;
					break;
				case(0x8):
					color = Color::BLACK;
					break;
				default:
					color = Color::RED;
				}
				spawnObject(level, color);
				waves.pop();
			}
			else if (objects.empty())
			{
				currentState = GameStates::WIN;
			}
			i++;
		} while (i < 2 && level > 2); // only spawn two cars if we're on level 3
	}
}

void Level::restartState()
{
	GameState::restartState();
	std::queue<unsigned char> empty;
	std::swap(waves, empty);

	initializeLevel();
}

Level::Level(std::shared_ptr<sf::RenderWindow> renderWindow, int level, std::string path, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard, GameStats* gameStats)
	: GameState(renderWindow, states, textures, fonts, soundBuffers, leaderboard, gameStats), levelPath(path), level(level)
{
	GameState::setGameLevel(level);
	initializeLevel();
}

Level::~Level()
{
}