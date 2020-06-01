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
	//player texture
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
	spawnPlayer();

	for (int i = 0; i < backgrounds.size(); i++)
		backgrounds[i].setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x * (i + 1)),
			static_cast<float>(renderWindow->getSize().y)));

	for (sf::RectangleShape& rs : backgrounds)
		rs.setTexture(&textures.at("BACKGROUND"));
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
		case Red:
			objects.push_back(new Object(Obstacle, level, textures.at("RED_CAR"), 280, 100));
			break;
		case Yellow:
			objects.push_back(new Object(Obstacle, level, textures.at("YELLOW_CAR"), 280, 100));
			break;
		case Orange:
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
		// MOVE UP
		player->updateMovement(-1);
	}
	else if (sf::Keyboard::D == keyCode ||
		sf::Keyboard::Down == keyCode)
	{
		// MOVE DOWN
		player->updateMovement(1);
	}
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

void GameState::updateBackground(const float& deltaTime)
{
	// SOMETHING LIKE:
	for (int i = 0; i < backgrounds.size(); i++) {
		backgrounds[i].move(2 * speed * deltaTime, 0);
		if (backgrounds[i].getPosition().x + backgrounds[i].getSize().x < 0)
			backgrounds[i].move(sf::Vector2f(static_cast<float>(2 * renderWindow->getSize().x), 0));
	}
}

void GameState::updateState(const float& deltaTime)
{
	if (!paused)
	{
		updateGameSpeed(deltaTime);
		updateBackground(deltaTime);
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