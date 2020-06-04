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

	Leaderboard leaderboard;

	// Delta Time
	sf::Clock deltaTimeClock;
	float deltaTime;

	// States
	std::stack<State*> states;

	// Initialization
	void initializeLeaderboard();
	void initializeWindow();
	void initializeStates();

public:
	// Constructors/Destructors
	Game();
	virtual ~Game();

	/* Functions */
	// Regular
	void endApplication();

	// Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void updateGame();

	// Render
	void renderGame();

	// Core
	void runGame();
};