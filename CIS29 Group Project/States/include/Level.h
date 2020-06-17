#pragma once

#include "GameState.h"

unsigned char leftNibble(unsigned char data);
unsigned char rightNibble(unsigned char data);

class Level : public GameState
{
private:
	// Variables
	const int level;
	const std::string levelPath;
	std::queue<unsigned char> waves;

	// Initializers
	void initializeLevel();

	// Functions
	void updateSpawning();
	void restartState();

public:
	Level(std::shared_ptr<sf::RenderWindow> renderWindow, int level, std::string path, std::stack<std::unique_ptr<State>>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard, GameStats* gameStats);
	~Level();
};
