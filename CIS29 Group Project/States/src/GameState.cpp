#include "stdafx.h"
#include "GameState.h"
#include "CollisionDetection.h"

void GameState::togglePause()
{
	paused = !paused;
}

//Initializers
void GameState::initializeTextures()
{
	//player texture
	try
	{
		if (!textures["PLAYER"].loadFromFile("Resources/Images/motorbiker(test player).png"))
		{
			throw std::invalid_argument("Resources/Images/motorbiker(test player).png");
		}

		if (!textures["RED_CAR"].loadFromFile("Resources/Images/CarFramesRed.png"))
		{
			throw std::invalid_argument("Resources/Images/CarFramesRed.png");
		}

		if (!textures["YELLOW_CAR"].loadFromFile("Resources/Images/CarFramesYellow.png"))
		{
			throw std::invalid_argument("Resources/Images/CarFramesYellow.png");
		}

		if (!textures["ORANGE_CAR"].loadFromFile("Resources/Images/CarFramesOrange.png"))
		{
			throw std::invalid_argument("Resources/Images/CarFramesOrange.png");
		}

		if (!backgroundTexture.loadFromFile("Resources/Images/GameBackground.png"))
		{
			throw std::invalid_argument("Resources/Images/GameBackground.png");
		}

		if (!textures["HEART"].loadFromFile("Resources/Images/Heart.png"))
		{
			throw std::invalid_argument("Resources/Images/Heart.png"); 
		}
	}
	catch (const std::invalid_argument& error)
	{
		std::cout << error.what() << std::endl;
		exit(-1);
	}

	for (int i = 0; i < backgrounds.size(); i++)
		backgrounds[i].setTexture(&backgroundTexture);
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states), pauseState(renderWindow, states)
{
	for (int i = 0; i < backgrounds.size(); i++)
		backgrounds[i].setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x), static_cast<float>(renderWindow->getSize().y)));

	backgrounds[1].move(sf::Vector2f(static_cast<float>(renderWindow->getSize().x), 0));

	speed = -75;
	frequency = 5;
	paused = false;
	this->states = states;
	initializeTextures();
}

GameState::~GameState()
{
	delete player;
	while (!objects.empty())
	{
		delete objects.front();
		objects.pop_front();
	}
}

void GameState::spawnPlayer()
{
	player = new Player(textures.at("PLAYER"));


	hud = new HUD(player, textures.at("HEART"));

	std::cout << "Player Spawned" << std::endl;
	player->resetClock();
}

void GameState::spawnObject(unsigned short level, unsigned short type)
{
	if (type == Red)
		objects.push_back(new Obstacle(level, textures.at("RED_CAR"), 280, 100));
	if (type == Yellow)
		objects.push_back(new Obstacle(level, textures.at("YELLOW_CAR"), 280, 100));
	if (type == Orange)
		objects.push_back(new Obstacle(level, textures.at("ORANGE_CAR"), 280, 100));
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

	std::cout << "player moving" << std::endl;
	if (sf::Keyboard::W == keyCode ||
		sf::Keyboard::Up == keyCode)
	{
		player->updateMovement(-1);
		// MOVE UP
	}
	else if (sf::Keyboard::D == keyCode ||
		sf::Keyboard::Down == keyCode)
	{
		// MOVE DOWN
		player->updateMovement(1);
	}

}

void GameState::updateObjects(const float& deltaTime)
{
	if (objects.front()->getCurrentPosition() <= - objects.front()->getWidth())
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

void GameState::updateBackground(const float& deltaTime)
{
	// SOMETHING LIKE:
	for (int i = 0; i < backgrounds.size(); i++) {
		backgrounds[i].move(speed * deltaTime, 0);
		if (backgrounds[i].getPosition().x+ backgrounds[i].getSize().x < 0)
			backgrounds[i].move(sf::Vector2f(static_cast<float>(2*renderWindow->getSize().x), 0));
	}
}

//Collision Detection
void GameState::checkCollision() {
	if (objects.front()->hit == false && CollisionDetection::PixelPerfectTest(player->getSprite(), objects.front()->getSprite()))
	{
		std::cout << "Collision!!!" << std::endl;
		//implement timer
		player->takeDamage();
		std::cout << "Player hearts: " << player->getCurrentHealth() << std::endl;
		objects.front()-> hit = true;
		if (player->getCurrentHealth() == 0) {
			togglePause(); //for now pausing the screen when player collides with cars 3 times
		}

	}
	
}

// Render
void GameState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	for (int i = 0; i < backgrounds.size(); i++)
		renderTarget->draw(backgrounds[i]);

	for (auto it : objects)
	{
		it->render(renderTarget);
	}

	if (player != nullptr) {
		player->render(renderTarget);
		hud->render(renderTarget);
	}

	if (paused)
	{
		pauseState.renderState(renderTarget);
	}
}
