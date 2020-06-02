#include "stdafx.h"
#include "GameState.h"
#include "CollisionDetection.h"
#include "ExceptionHandler.h"

void GameState::togglePause()
{
	paused = !paused;
}

//Initializers
void GameState::initializeTextures()
{
	if (!textures["PLAYER"].loadFromFile("Resources/Images/motorbiker(test player).png") ||
		!textures["RED_CAR"].loadFromFile("Resources/Images/CarFramesRed.png") ||
		!textures["YELLOW_CAR"].loadFromFile("Resources/Images/CarFramesYellow.png") ||
		!textures["ORANGE_CAR"].loadFromFile("Resources/Images/CarFramesOrange.png") ||
		!textures["BACKGROUND"].loadFromFile("Resources/Images/GameBackground.png") ||
		!textures["HEART"].loadFromFile("Resources/Images/Heart.png"))
		exit(-1); // the loadFromFile() function has an ouput
				  // when it fails so no need to throw
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states), pauseState(renderWindow, states),
	speed(-75), frequency(5), states(states), paused(false)
{
	initializeTextures();

	for (int i = 0; i < backgrounds.size(); i++)
	{
		backgrounds[i].setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x * (i + 1)),
			static_cast<float>(renderWindow->getSize().y)));
		backgrounds[i].setTexture(&textures.at("BACKGROUND"));
	}
}

GameState::~GameState()
{
	delete player;
	delete hud;
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
	try {
		switch (type)
		{
		case RED:
			objects.push_back(new Object(Obstacle, level, textures.at("RED_CAR"), 280, 100));
			break;
		case YELLOW:
			objects.push_back(new Object(Obstacle, level, textures.at("YELLOW_CAR"), 280, 100));
			break;
		case ORANGE:
			objects.push_back(new Object(Obstacle, level, textures.at("ORANGE_CAR"), 280, 100));
			break;
		default:
			throw exc::SpawnError<unsigned short>(type);
			break;
		}
	}
	catch (exc::SpawnError<unsigned short>& error)
	{
		std::cout << error.what();
		exit(-1);
	}
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

void GameState::updateKeyboard(unsigned short keyCode)
{
	if (paused)
		pauseState.updateKeyboard(keyCode);

	if (sf::Keyboard::Escape == keyCode)
	{
		togglePause();
	}

	if (sf::Keyboard::W == keyCode ||
		sf::Keyboard::Up == keyCode)
	{
		// MOVE UP
		player->updateMovement(-1);
	}
	else if (sf::Keyboard::S == keyCode ||
		sf::Keyboard::Down == keyCode)
	{
		// MOVE DOWN
		player->updateMovement(1);
	}
}

void GameState::updateMouseWheel(short mouseDelta)
{
	// Any Unique Pause State Mouse Wheel Input
}

void GameState::updateGameSpeed(const float& deltaTime)
{
	spawnTime += deltaTime;

	speed -= deltaTime * 10.f;

	// UPDATE THE SPAWNING FREQUENCY
	frequency = -35.f / (speed * deltaTime);
}

void GameState::updateObjects(const float& deltaTime)
{
	if (objects.front()->getCurrentPosition() <= -objects.front()->getWidth())
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

void GameState::updateBackground(const float& deltaTime, const short dir)
{
	// SOMETHING LIKE:
	for (sf::RectangleShape& background : backgrounds) {
		background.move(2 * speed * dir * deltaTime, 0);

		if (dir > 0 && background.getPosition().x + background.getSize().x < 0)
			background.move(sf::Vector2f(2.f * renderWindow->getSize().x, 0.f));
		if (dir < 0 && background.getPosition().x > 0)
			background.move(sf::Vector2f(-1.f * renderWindow->getSize().x, 0.f));
	}
}

void GameState::updateState(const float& deltaTime)
{
	if (!paused)
	{
		updateGameSpeed(deltaTime);
		updateBackground(deltaTime, FORWARDS);
		updateSpawning();
		player->updateScore(deltaTime);
		hud->update();

		if (!objects.empty())
		{
			checkCollision();
			updateObjects(deltaTime);
		}
	}
	else
	{
		pauseState.updateState(deltaTime);
		updateGUI();
	}
}

//Collision Detection
void GameState::checkCollision() {
	if (objects.front()->hit == false && CollisionDetection::PixelPerfectTest(player->getSprite(), objects.front()->getSprite()))
	{
		switch (objects.front()->type)
		{
		case Obstacle:
			std::cout << "Collision!!!" << std::endl;
			//implement timer
			player->takeDamage();
			std::cout << "Player hearts: " << player->getCurrentHealth() << std::endl;
			objects.front()->hit = true;
			if (player->getCurrentHealth() == 0) {
				togglePause(); //for now pausing the screen when player collides with cars 3 times
			}
			break;
		case Coin:
			player->gainCoin();
			break;
		default:
			break;
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
		it->render(renderTarget);

	if (player != nullptr)
		player->render(renderTarget);

	if (hud != nullptr)
		hud->render(renderTarget);

	if (paused)
		pauseState.renderState(renderTarget);
}