#pragma once

#include "GameState.h"

class FreePlayState :
	public GameState
{
private:
	// Variables
	std::random_device randomDevice;

	// Functions
	void updateSpawning();
public:
	FreePlayState(sf::RenderWindow* renderWindow, std::stack<State*>* states, std::map<std::string, sf::Texture>* textures, Leaderboard* leaderboard);
	~FreePlayState();
};
