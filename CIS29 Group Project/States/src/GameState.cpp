#include "stdafx.h"
#include "GameState.h"

void GameState::togglePause()
{
	paused = !paused;
}

//Initializers
void GameState::initializeBackground()
{
	if (!textures["OBSTACLE"].loadFromFile("Resources/Images/CarFrames.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}

	if (!backgroundTexture.loadFromFile("Resources/Images/GameBackground.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgroundTexture);
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states), pauseState(renderWindow, states)
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x), static_cast<float>(renderWindow->getSize().y)));
	speed = -75;
	frequency = 2;
	paused = false;
	this->states = states;
	initializeBackground();
}

GameState::~GameState()
{
	while (!objects.empty())
	{
		delete objects.front();
		objects.pop_front();
	}
}

void GameState::spawnObject(unsigned short level, unsigned short type)
{
	// TEMP, REMOVE LATER
	type = OBSTICLE;

	if (type == OBSTICLE)
		objects.push_back(new Obstacle(level, textures.at("OBSTACLE"), sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(320, 320))));

	std::cout << "OBSTICLE SPAWNED!!!" << std::endl;
	std::cout << type << " at " << level << std::endl;
}

/* Functions */
// Update


void GameState::updateGUI()
{
	if (paused)
	{
		// Resume the Game
		if (pauseState.isButtonPressed("RESUME"))
		{
			togglePause();
		}

		// Quit This Game
		if (pauseState.isButtonPressed("QUIT"))
		{
			quitState();
		}
	}
}

void GameState::updateInput(unsigned short keyCode)
{
	if (paused)
		pauseState.updateInput(keyCode);

	if (sf::Keyboard::Escape == keyCode)
	{
		togglePause();
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

void GameState::updateObjects(const float& deltaTime)
{
	if (objects.front()->getCurrentPosition() <= 0.f) // MAY NEED TO ADJUST BASED ON CENTER OF OBEJCT
	{
		delete objects.front();
		objects.pop_front();
	}

	for (auto it : objects)
	{
		it->move(speed, deltaTime);
		it->update(deltaTime);
	}
}

// Render
void GameState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);
	if (paused)
	{
		pauseState.renderState(renderTarget);
	}

	for (auto it : objects)
	{
		it->render(renderTarget);
	}
}
