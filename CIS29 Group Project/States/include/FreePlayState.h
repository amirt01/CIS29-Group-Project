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
	FreePlayState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard, GameStats* gameStats);
	~FreePlayState();
};
