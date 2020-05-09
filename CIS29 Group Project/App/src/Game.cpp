#include "stdafx.h"
#include "Game.h"

//Initializers
void Game::initVariables()
{
}

void Game::initializeWindow()
{
	renderWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "CIS29 Group Project");
}

// Constructor / Destructors
Game::Game()
{
    initializeWindow();
}

Game::~Game()
{
	delete renderWindow;
}

/* Functions */
void Game::endApplication()
{
}

// Updates
void Game::updateDeltaTime()
{
    deltaTime = deltaTimeClock.restart().asSeconds();

    /* Use to print deltaTime to consol */
    system("cls");
    std::cout << deltaTime;
}

void Game::updateSFMLEvents()
{
    sf::Event event;
    while (renderWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            renderWindow->close();
    }
}

void Game::updateGame()
{
    updateSFMLEvents();
}

// Core
void Game::renderGame()
{
    renderWindow->clear();
    
    // Render Items

    renderWindow->display();
}

void Game::runGame()
{
    while (renderWindow->isOpen())
    {
        updateDeltaTime();
		updateSFMLEvents();
		updateGame();
		renderGame();
    }
}
