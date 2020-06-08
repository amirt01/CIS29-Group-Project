#pragma once

#include "State.h"
#include "Leaderboard.h"

class Game
{
private:
	// Variables
	sf::RenderWindow* renderWindow;
	sf::Event event;

	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	std::map<std::string, sf::Texture> textures;

	Leaderboard leaderboard;

	// Delta Time
	sf::Clock deltaTimeClock;
	float deltaTime;

	// States
	std::stack<State*> states;

	// Initialization
	void initializeLeaderboard(std::string path);
	void initializeWindow(std::string path);
	void initializeStates();
	void initializeTextures();

public:
	// Constructors/Destructors
	Game();
	virtual ~Game();

	/* Functions */
	// Regular
	void endApplication(std::string leaderboardPath);

	// Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void updateGame();

	// Render
	void renderGame();

	// Core
	void runGame();
};