#pragma once

#include "GameState.h"

unsigned char leftNibble(unsigned char data);
unsigned char rightNibble(unsigned char data);

class Level : public GameState
{
private:
	// Variables
	std::queue<unsigned char> waves;

	// Initializers
	void initializeLevel(std::string path);

	// Functions
	void updateSpawning();
public:
	Level(sf::RenderWindow* renderWindow, std::string path, std::stack<State*>* states, std::map<std::string, sf::Texture>* textures, Leaderboard* leaderboard);
	~Level();
};
