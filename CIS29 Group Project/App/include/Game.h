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

	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

	Leaderboard leaderboard;

	// Delta Time
	sf::Clock deltaTimeClock;
	float deltaTime;

	// States
	std::stack<State*> states;

	// Initialization
	void initializeLeaderboard(std::string path);
	void initializeWindow(std::string path);

	void initializeTextures();
	void initializeFonts();
	void initializeAudio();

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