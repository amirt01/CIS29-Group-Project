#pragma once

#include "GameState.h"

enum level { TOP = 0, MIDDLE, BOTTOM };
enum obsticle { MEDIUM = 0, LARGE, SMALL};

class FreePlayState :
	public GameState
{
private:
	// Variables
	std::random_device randomDevice;

	sf::Clock GameClock;
	sf::Clock spawnClock;
	bool readyToSpawn;

	short unsigned level;
	short unsigned obsticle;

	// Initializers
	void initializeVariables();

	// Functions
	bool checkForSpawn();
	void updateSpawnClock();
	void spawnObsticle();
public:
	FreePlayState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	~FreePlayState();

	// Functions
	void updateRNG();
	void updateState(const float& deltaTime);
};

