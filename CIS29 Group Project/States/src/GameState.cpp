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

void GameState::initializeTextures()
{
	if (!textures["PLAYER_IDLE"].loadFromFile("Resources/Images/temp_idle.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}
}

void GameState::initializePlayer()
{
	player = new Player(20.f, 310.f, textures["PLAYER_IDLE"]);

	// REMOVE LATER
	enemy = new Enemy(1000.f, 310.f, 300.f, player, textures["PLAYER_IDLE"]);
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states)
{
	this->states = states;
	initializeBackground();
	initializeTextures();
	initializePlayer();
}

GameState::~GameState()
{
	delete enemy;
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
		player->move(UP);
	}
	else if (sf::Keyboard::S == keyCode ||
			 sf::Keyboard::Down == keyCode)
	{
		player->move(DOWN);
	}
}

void GameState::updateState(const float& deltaTime)
{
	enemy->move(-0.5f, deltaTime);
	enemy->update(deltaTime);

	std::cout << "Running GameState" << std::endl;
}

// Render
void GameState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);
	enemy->render(renderTarget);
	player->render(renderTarget);
}
