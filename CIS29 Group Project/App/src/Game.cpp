#include "stdafx.h"

#include "Constants.h"
#include "ExceptionHandler.h"
#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"

// Initializers
void Game::initializeLeaderboard(std::string path)
{
	try
	{
		if (!leaderboard.loadFromFile(fonts.at("DOSIS-BOLD"), path))
			throw exc::LoadFromFileError(path);
	}
	catch (exc::LoadFromFileError& error)
	{
		std::cout << error.what();
		exit(EXIT_FAILURE);
	}
}

void Game::initializeWindow(std::string path)
{
	std::ifstream fin(path);
	std::string game_title;
	sf::VideoMode render_window_bounds;
	bool fullscreen;
	unsigned framerate_limit;
	sf::VideoMode window_bounds;
	bool vertical_sync_enabled;
	unsigned antialiasing_level;

	try
	{
		/*
		Game Title
		render window width _ render window height
		fullscreen
		framerate limit
		vertical sync enabled
		antialiasing
		*/

		if (fin.is_open())
		{
			std::getline(fin, game_title);
			fin >> window_bounds.width >> window_bounds.height;
			fin >> fullscreen;
			fin >> framerate_limit;
			fin >> vertical_sync_enabled;
			fin >> antialiasing_level;
		}
		else
			throw exc::LoadFromFileError(path);
	}
	catch (exc::LoadFromFileError&) {
		unsigned int in;

		std::cout << "Error reading file window setting's file. "
			<< "(1) Load Default Settings\n"
			<< "(2) Exit\n";
		std::cin >> in;

		if (in == 1)
		{
			game_title = "DEFAULT";
			render_window_bounds.height = 720;
			render_window_bounds.width = 1280;
			fullscreen = false;
			framerate_limit = 120;
			window_bounds = sf::VideoMode::getDesktopMode();
			vertical_sync_enabled = false;
			antialiasing_level = 0;
		}
		else
			exit(EXIT_FAILURE);
	}

	fin.close();

	/*Adjust window as needed*/
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if (fullscreen)
		renderWindow = new sf::RenderWindow(window_bounds, game_title, sf::Style::Fullscreen, windowSettings);
	else
		renderWindow = new sf::RenderWindow(window_bounds, game_title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	renderWindow->setFramerateLimit(framerate_limit);
	renderWindow->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initializeTextures()
{
	std::for_each(TEXTRUE_PATHS.begin(), TEXTRUE_PATHS.end(), [this](const auto& texturePair) {
		if (!textures[texturePair.first].loadFromFile(texturePair.second))
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
	: leaderboard(MAX_NUM_OF_SCORES), deltaTime(0.f)
{
	initializeTextures();
	initializeFonts();
	initializeAudio();
	initializeLeaderboard(LEADERBOARD_PATH);
	initializeWindow(SFML_WINDOW_SETTINGS_PATH);
	states.push(new MainMenuState(renderWindow, &states, &textures, &fonts, &soundBuffers, &leaderboard));
}

Game::~Game()
{
	delete renderWindow;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

// Functions
void Game::endApplication(std::string leaderboardPath)
{
	// Save Leaderboard Data
	try
	{
		if (!leaderboard.writeToFile(leaderboardPath))
			throw exc::WriteToFileError(leaderboardPath);
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
		delete states.top();
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
	{
		renderWindow->close();
	}

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

	endApplication("Config/leaderboard.txt");
}