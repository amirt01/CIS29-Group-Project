#pragma once

#include "GameState.h"

unsigned char leftNibble(unsigned char data);
unsigned char rightNibble(unsigned char data);

class Level : public GameState
{
private:
	// Variables
	sf::Clock spawnClock;

	std::queue<unsigned char> waves;

	// Initializers
	void initializeVariables();
	void initializeLevel(std::string path);

	// Functions
	bool checkForSpawn();
	void updateSpawnClock();
	void spawnObsticle(unsigned short level, unsigned short type);
public:
	Level(sf::RenderWindow* renderWindow, std::string path, std::stack<State*>* states);
	~Level();

	// Functions
	void updateState(const float& deltaTime);
};

