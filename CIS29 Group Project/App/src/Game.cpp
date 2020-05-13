#include "stdafx.h"

#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"

//Initializers
void Game::initializeVariables()
{
    deltaTime = 0.f;
}

void Game::initializeWindow()
{
    std::ifstream fin("Config/render_window_settings.txt");

    /*
    Game Title
    render window width _ render window height
    fullscreen
    framerate limit
    vertical sync enabled
    antialiasing
    */

    std::string game_title = "DEFAULT";
    sf::VideoMode render_window_bounds(1280, 720);
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

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
    {
        std::cout << "Error reading file window setting's file. "
            << "Loading default settings..." << std::endl;
        system("PAUSE");
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

void Game::initializeStates()
{
    states.push(new MainMenuState(renderWindow, &states));
}

// Constructor / Destructors
Game::Game()
{
    initializeVariables();
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
        switch (event.type)
        {
        case(sf::Event::Closed):
            renderWindow->close();
        case(sf::Event::EventType::KeyPressed):
            states.top()->updateInput(event.key.code);
        default:
            break;
        }
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
        sf::Event event;

        updateDeltaTime();
        updateSFMLEvents();
        updateGame();
        renderGame();
    }
}