#include "stdafx.h"

#include "Constants.h"
#include "loadFromFileError.h"
#include "WriteToFileError.h"
#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "CollisionDetection.h"

// Initializers
void Game::initializePackages(std::string leaderboardPath, std::string gameStatsPath)
{
	try
	{
		if (!leaderboard.loadFromFile(fonts.at("DOSIS-BOLD"), leaderboardPath))
			throw exc::LoadFromFileError(leaderboardPath);
		if (!gameStats.loadFromFile(gameStatsPath))
			throw exc::LoadFromFileError(gameStatsPath);
		if (!graphicsSettings.loadFromFile(SFML_WINDOW_SETTINGS_PATH))
			throw exc::LoadFromFileError(SFML_WINDOW_SETTINGS_PATH);
	}
	catch (exc::LoadFromFileError& error)
	{
		std::cout << error.what();
		exit(EXIT_FAILURE);
	}
}

void Game::initializeWindow(std::string path)
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
		if (!CollisionDetection::CreateTextureAndBitmask(textures[texturePair.first], texturePair.second))
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
	initializePackages(LEADERBOARD_PATH, GAME_STATS_PATH);
	initializeWindow(SFML_WINDOW_SETTINGS_PATH);
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
		if (!leaderboard.writeToFile(leaderboardPath))
			throw exc::WriteToFileError(leaderboardPath);
		if (!gameStats.writeToFile(gameStatsPath))
			throw exc::WriteToFileError(gameStatsPath);
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
	std::cout << "Running " << states.top()->name() << std::endl;
	if (states.top()->getQuit())
	{
		states.top()->quitState();
		states.pop();
	}
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