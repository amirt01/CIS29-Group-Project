#include "stdafx.h"
#include "FreePlayState.h"

void FreePlayState::updateSpawning()
{
	if (spawnTime >= frequency) // ready to spawn
	{
		spawnTime = 0;

		unsigned short spawnLevel1 = randomDevice() % 3;
		unsigned short spawnLevel2 = randomDevice() % 3;

		spawnObject(static_cast<unsigned short>(spawnLevel1),  // random position
			static_cast<unsigned short>(randomDevice() % 3)); // random color

		if (spawnLevel1 == spawnLevel2)
		{
			std::array<unsigned short, 2> spawnLevels;

			switch (spawnLevel1)
			{
			case 0:
				spawnLevels = { 1, 2 };
				break;
			case 1:
				spawnLevels = { 0, 2 };
				break;
			case 2:
				spawnLevels = { 0, 1 };
				break;
			default:
				break;
			}

			spawnLevel2 = spawnLevels[randomDevice() % 2];
		}

		spawnObject(static_cast<unsigned short>(spawnLevel2),  // random position
			static_cast<unsigned short>(randomDevice() % 3)); // random color
	}
}

FreePlayState::FreePlayState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard, GameStats* gameStats)
	: GameState(renderWindow, states, textures, fonts, soundBuffers, leaderboard, gameStats)
{
}

FreePlayState::~FreePlayState()
{
}