#include "stdafx.h"
#include "GameState.h"
#include "CollisionDetection.h"

void GameState::togglePause()
{
	paused = !paused;
}

class TextureError : public std::invalid_argument
{
public:
	TextureError(std::string path) : std::invalid_argument(path) {};
};

//Initializers
void GameState::initializeTextures()
{
	//player texture
	try
	{
		if (!textures["PLAYER"].loadFromFile("Resources/Images/motorbiker(test player).png"))
		{
			throw TextureError("Resources/Images/motorbiker(test player).png");
		}

		if (!textures["RED_CAR"].loadFromFile("Resources/Images/CarFramesRed.png"))
		{
			throw TextureError("Resources/Images/CarFramesRed.png");
		}

		if (!textures["YELLOW_CAR"].loadFromFile("Resources/Images/CarFramesYellow.png"))
		{
			throw TextureError("Resources/Images/CarFramesYellow.png");
		}

		if (!textures["ORANGE_CAR"].loadFromFile("Resources/Images/CarFramesOrange.png"))
		{
			throw TextureError("Resources/Images/CarFramesOrange.png");
		}

		if (!backgroundTexture.loadFromFile("Resources/Images/GameBackground.png"))
		{
			throw TextureError("Resources/Images/GameBackground.png");
		}
	}
	catch (const TextureError& error)
	{
		std::cout << error.what() << std::endl;
		exit(-1);
	}


	background.setTexture(&backgroundTexture);
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states), pauseState(renderWindow, states)
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x), static_cast<float>(renderWindow->getSize().y)));
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
	background.move(speed * deltaTime, 0);
}

//Collision Detection
void GameState::checkCollision() {
	if (CollisionDetection::PixelPerfectTest(player->getSprite(), objects.front()->getSprite()))
	{
		std::cout << "Collision!!!" << std::endl;
	}
	

	/**
	Collision objC(objects.front()->getCollision());
	if (player->getCollision().checkCollision(objC, 100)) {
		std::cout << "Collision!!!" << std::endl;
	}**/
}

// Render
void GameState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);

	for (auto it : objects)
	{
		it->render(renderTarget);
	}

	if (paused)
	{
		pauseState.renderState(renderTarget);
	}

	if (player != nullptr) {
		player->render(renderTarget);
	}
}
