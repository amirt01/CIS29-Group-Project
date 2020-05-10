#include "stdafx.h"
#include "GameState.h"

//Initializers
void GameState::initializeBackground()
{
	background.setSize(sf::Vector2f(renderWindow->getSize().x, renderWindow->getSize().y));

	if (!backgroundTexture.loadFromFile("Resources/Images/temp_background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgroundTexture);
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states)
{
	this->states = states;
	initializeBackground();
}

GameState::~GameState()
{
}

/* Functions */
// Update
void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		quitState();
	}
}

void GameState::updateState(const float& deltaTime)
{
	updateInput(deltaTime);

	std::cout << "Running GameState" << std::endl;
}

// Render
void GameState::renderState(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(background);
}
