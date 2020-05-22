#include "stdafx.h"

#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"

//Initializers
void Game::initializeVariables()
{
    deltaTime = 0.f;
}

void Game::initGraphicsSettings()
{
    graphicsSettings.loadFromFile("Config/render_window_settings.txt");
}

void Game::initializeWindow()
{
    /* Creates a SFML window */
    if (graphicsSettings.fullscreen)
        renderWindow = new sf::RenderWindow(graphicsSettings.windowBounds, graphicsSettings.gameTitle, sf::Style::Fullscreen, graphicsSettings.contextSettings);
    else
        renderWindow = new sf::RenderWindow(graphicsSettings.resolution, graphicsSettings.gameTitle, sf::Style::Titlebar | sf::Style::Close, graphicsSettings.contextSettings);

    renderWindow->setFramerateLimit(graphicsSettings.framerateLimit);
    renderWindow->setVerticalSyncEnabled(graphicsSettings.verticalSyncEnabled);
}

void Game::initializeStates()
{
    states.push(new MainMenuState(renderWindow, graphicsSettings, &states));
}

// Constructor / Destructors
Game::Game()
{
    initializeVariables();
    initGraphicsSettings();
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
        updateDeltaTime();
        updateSFMLEvents();
        updateGame();
        renderGame();
    }
}