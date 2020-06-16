#pragma once

#include "State.h"
#include "Leaderboard.h"
#include "GameStats.h"
#include "GraphicsSettings.h"

class Game
{
private:
	// Variables
	GraphicsSettings graphicsSettings;
	std::shared_ptr<sf::RenderWindow> renderWindow;
	sf::Event event;

	// Graphics Settings
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	// Loaded From Files
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

	// Packages
	Leaderboard leaderboard;
	GameStats gameStats;

	// Delta Time
	sf::Clock deltaTimeClock;
	float deltaTime;

	// States
	std::stack<std::unique_ptr<State>> states;

	// Initialization
	void initializePackages();
	void initializeWindow();

	void initializeTextures();
	void initializeFonts();
	void initializeAudio();

public:
	// Constructors/Destructors
	Game();
	virtual ~Game();

	/* Functions */
	// Regular
	void endApplication(std::string leaderboardPath, std::string gameStatsPath);

	// Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void updateGame();

	// Render
	void renderGame();

	// Core
	void runGame();
};