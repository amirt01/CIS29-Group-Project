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
	FreePlayState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard);
	~FreePlayState();
};
