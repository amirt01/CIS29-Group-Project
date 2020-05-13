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
void GameState::updateInput(unsigned short keyCode)
{
	if (sf::Keyboard::Escape == keyCode)
	{
		quitState();
	}
	if (sf::Keyboard::W == keyCode ||
		sf::Keyboard::Up == keyCode)
	{
		// MOVE UP
	}
	else if (sf::Keyboard::D == keyCode ||
		sf::Keyboard::Down == keyCode)
	{
		// MOVE DOWN
	}
}

void GameState::updateState(const float& deltaTime)
{
	// MOVE ENEMY
	// UPDATE ENEMY

	std::cout << "Running GameState" << std::endl;
}

// Render
void GameState::renderState(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(background);
}
