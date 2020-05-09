#include "stdafx.h"
#include "Game.h"

//Initializers
void Game::initVariables()
{
}

void Game::initializeWindow()
{
    std::ifstream fin("Config/window.txt");
    
    /*
    Game Title
    render window width _ render window height
    framerate limit
    vertical sync enabled
    */
    
    std::string game_title = "DEFAULT";
    sf::VideoMode render_window_bounds(800, 600);
    unsigned framerate_limt = 120;
    bool vertical_sync_enabled = false;

    if (fin.is_open())
    {
        std::getline(fin, game_title);
        fin >> render_window_bounds.width >> render_window_bounds.height;
        fin >> framerate_limt;
        fin >> vertical_sync_enabled;
    }
    else
    {
        std::cout << "Error reading file window setting's file." << std::endl;
        system("PAUSE");
    }

    fin.close();

	renderWindow = new sf::RenderWindow(render_window_bounds, game_title);
    renderWindow->setFramerateLimit(framerate_limt);
    renderWindow->setVerticalSyncEnabled(vertical_sync_enabled);
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
