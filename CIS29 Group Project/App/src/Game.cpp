#include "stdafx.h"

#include "Game.h"
#include "GameState.h"

//Initializers
void Game::initializeVariables()
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

void Game::initializeStates()
{
    states.push(new GameState(renderWindow));
}

// Constructor / Destructors
Game::Game()
{
    initializeWindow();
    initializeStates();
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

/* Functions */
void Game::endApplication()
{
    std::cout << "Application is closing...";
}

// Updates
void Game::updateDeltaTime()
{
    deltaTime = deltaTimeClock.restart().asSeconds();

    /* Use to print deltaTime to consol */
    system("cls");
    std::cout << deltaTime << std::endl;
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

    if (!states.empty())
    {
        states.top()->updateState(deltaTime);
        if (states.top()->getQuit())
        {
            states.top()->quitState();
            delete states.top();
            states.pop();
        }
    }
    // states stack is empty, quit application
    else
    {
        endApplication();
        renderWindow->close();
    }
}

// Core
void Game::renderGame()
{
    renderWindow->clear();
    
    if (!states.empty())
        states.top()->renderState(renderWindow);

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
