#pragma once

#include "State.h"

class Game
{
private:
	// Variables
	sf::RenderWindow* renderWindow;
	sf::Event event;

	// Delta Time
	sf::Clock deltaTimeClock;
	float deltaTime;

	// States
	std::stack<State*> states;

	// Initialization
	void initializeVariables();
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