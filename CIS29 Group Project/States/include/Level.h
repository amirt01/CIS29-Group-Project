#pragma once

#include "GameState.h"

class Level : public GameState
{
	// Variables
	float frequency;
	sf::Clock spawnClock;

	std::queue<

	// Initializers
	void initializeVariables();
	void initializeLevel(std::string path);

	// Functions
	std::pair<short, short> setObsticleStates();
	bool checkForSpawn();
	void updateSpawnClock();
	void spawnObsticle(std::pair<short, short> obsticleStats);
public:
	Level(sf::RenderWindow* renderWindow, std::string path, std::stack<State*>* states);
	~Level();

	// Functions
	void updateState(const float& deltaTime);
};

