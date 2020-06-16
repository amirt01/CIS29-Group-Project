#include "stdafx.h"

#include "Constants.h"
#include "loadFromFileError.h"
#include "WriteToFileError.h"
#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "CollisionDetection.h"

// Initializers
void Game::initializePackages()
{
	try
	{
		if (!leaderboard.loadFromFile(fonts.at("DOSIS-BOLD"), LEADERBOARD_PATH))
			throw exc::LoadFromFileError(LEADERBOARD_PATH);
		if (!gameStats.loadFromFile(GAME_STATS_PATH))
			throw exc::LoadFromFileError(GAME_STATS_PATH);
		if (!graphicsSettings.loadFromFile(SFML_WINDOW_SETTINGS_PATH))
			throw exc::LoadFromFileError(SFML_WINDOW_SETTINGS_PATH);
	}
	catch (exc::LoadFromFileError& error)
	{
		std::cout << error.what();
		exit(EXIT_FAILURE);
	}
}

void Game::initializeWindow()
{
	if (graphicsSettings.fullscreen)
		renderWindow = std::make_shared<sf::RenderWindow>(
			graphicsSettings.resolution,
			graphicsSettings.gameTitle,
			sf::Style::Fullscreen,
			graphicsSettings.contextSettings);
	else
		renderWindow = std::make_shared<sf::RenderWindow>(
			graphicsSettings.resolution,
			graphicsSettings.gameTitle,
			sf::Style::Titlebar | sf::Style::Close,
			graphicsSettings.contextSettings);

	renderWindow->setFramerateLimit(graphicsSettings.frameRateLimit);
	renderWindow->setVerticalSyncEnabled(graphicsSettings.verticalSync);
}

void Game::initializeTextures()
{
	std::for_each(TEXTRUE_PATHS.begin(), TEXTRUE_PATHS.end(), [this](const auto& texturePair) {
		if (!Collision::CreateTextureAndBitmask(textures[texturePair.first], texturePair.second))
			exit(EXIT_FAILURE); // the loadFromFile() function has an ouput
								// when it fails so no need to throw
		});
}

void Game::initializeFonts()
{
	std::for_each(FONT_PATHS.begin(), FONT_PATHS.end(), [this](const auto& fontPair) {
		if (!fonts[fontPair.first].loadFromFile(fontPair.second))
			exit(EXIT_FAILURE); // the loadFromFile() function has an ouput
								// when it fails so no need to throw
		});
}

void Game::initializeAudio()
{
	std::for_each(AUDIO_PATHS.begin(), AUDIO_PATHS.end(), [this](const auto& audioPair) {
		if (!soundBuffers[audioPair.first].loadFromFile(audioPair.second))
			exit(EXIT_FAILURE); // the loadFromFile() function has an ouput
								// when it fails so no need to throw
		});
}

// Constructor / Destructors
Game::Game()
	: leaderboard(MAX_NUM_OF_SCORES), deltaTime(0.f), renderWindow(nullptr)
{
	initializeTextures();
	initializeFonts();
	initializeAudio();
	initializePackages();
	initializeWindow();
	states.push(std::make_unique<MainMenuState>(renderWindow, &states, &textures, &fonts, &soundBuffers, &leaderboard, &gameStats, &graphicsSettings));
}

Game::~Game()
{
	while (!states.empty())
	{
		states.pop();
	}
}

// Functions
void Game::endApplication(std::string leaderboardPath, std::string gameStatsPath)
{
	// Save Data
	try
	{
		if (!leaderboard.writeToFile(LEADERBOARD_PATH))
			throw exc::WriteToFileError(LEADERBOARD_PATH);
		if (!gameStats.writeToFile(GAME_STATS_PATH))
			throw exc::WriteToFileError(GAME_STATS_PATH);
		if (!graphicsSettings.writeToFile(SFML_WINDOW_SETTINGS_PATH))
			throw exc::WriteToFileError(SFML_WINDOW_SETTINGS_PATH);
	}
	catch (exc::WriteToFileError& error)
	{
		std::cout << error.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

// Updates
void Game::updateDeltaTime()
{
	deltaTime = deltaTimeClock.restart().asSeconds();

	// Use to print deltaTime to consol
	system("cls");
	std::cout << deltaTime << std::endl;
}

void Game::updateSFMLEvents()
{
	sf::Event event;
	while (renderWindow->pollEvent(event))
	{
		switch (event.type)
		{
		case(sf::Event::Closed):
			renderWindow->close();
		case(sf::Event::EventType::KeyPressed):
			states.top()->updateKeyboard(event.key.code);
		case(sf::Event::MouseButtonReleased):
			states.top()->updateMouseButtons(event.mouseButton.button);
		case(sf::Event::MouseWheelMoved):
			states.top()->updateMouseWheel(event.mouseWheel.delta);
		default:
			break;
		}
	}
}

void Game::updateGame()
{
	updateSFMLEvents();
	states.top()->updateState(deltaTime);
	if (!states.empty())
		std::cout << "Running " << states.top()->name() << std::endl;
}

// Core
void Game::renderGame()
{
	renderWindow->clear();

	if (!states.empty()) {
		states.top()->renderState(renderWindow);
	}
	else
		renderWindow->close();

	renderWindow->display();
}

void Game::runGame()
{
	while (renderWindow->isOpen())
	{
		updateDeltaTime();
		updateGame();
		renderGame();
	}

	endApplication(LEADERBOARD_PATH, GAME_STATS_PATH);
}