#include "stdafx.h"
#include "FreePlayState.h"

void FreePlayState::updateSpawning()
{
	if (spawnTime >= frequency) // ready to spawn
	{
		spawnTime = 0;

		Levels spawnLevel1 = static_cast<Levels>(randomDevice() % 3);
		Levels spawnLevel2 = static_cast<Levels>(randomDevice() % 3);

		spawnObject(spawnLevel1,  // random position
			static_cast<Color>(randomDevice() % 4)); // random color

		if (spawnLevel1 == spawnLevel2)
		{
			std::array<Levels, 2> spawnLevels;

			switch (spawnLevel1)
			{
			case Levels::BOTTOM:
				spawnLevels = { Levels::MIDDLE, Levels::TOP };
				break;
			case Levels::MIDDLE:
				spawnLevels = { Levels::BOTTOM, Levels::TOP };
				break;
			case Levels::TOP:
				spawnLevels = { Levels::BOTTOM, Levels::MIDDLE };
				break;
			default:
				break;
			}

			spawnLevel2 = static_cast<Levels>(spawnLevels[randomDevice() % 2]);
		}

		spawnObject(spawnLevel2,  // random position
			static_cast<Color>(randomDevice() % 4)); // random color
	}
}

FreePlayState::FreePlayState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard, GameStats* gameStats)
	: GameState(renderWindow, states, textures, fonts, soundBuffers, leaderboard, gameStats)
{
	GameState::setGameLevel(0);
}

FreePlayState::~FreePlayState()
{
}