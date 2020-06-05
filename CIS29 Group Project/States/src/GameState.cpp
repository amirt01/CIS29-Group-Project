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
		exit(EXIT_FAILURE); // the loadFromFile() function has an ouput
				  // when it fails so no need to throw
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states, Leaderboard* leaderboard)
	: State(renderWindow, states), pauseState(renderWindow, states), leaderboard(leaderboard),
	speed(-75), frequency(5), states(states), paused(false), spawnTime(frequency)
{
	initializeTextures();

	for (int i = 0; i < backgrounds.size(); i++)
	{
		backgrounds[i].setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
			static_cast<float>(renderWindow->getSize().y)));
		backgrounds[i].setPosition(static_cast<float>(renderWindow->getSize().x * (i - 1.f)), 0.f);
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

	player->resetClock();
}

void GameState::spawnObject(unsigned short level, unsigned short type)
{
	try {
		switch (type)
		{
		case RED:
			objects.push_back(new Object(Obstacle, level, textures.at("RED_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		case YELLOW:
			objects.push_back(new Object(Obstacle, level, textures.at("YELLOW_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		case ORANGE:
			objects.push_back(new Object(Obstacle, level, textures.at("ORANGE_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		default:
			throw exc::SpawnError<unsigned short>(type);
			break;
		}
	}
	catch (exc::SpawnError<unsigned short>& error)
	{
		std::cout << error.what();
		exit(EXIT_FAILURE);
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
		sf::Keyboard::Up == keyCode &&
		!paused)
	{
		// MOVE UP
		player->updateMovement(-1);
	}
	else if (sf::Keyboard::S == keyCode ||
		sf::Keyboard::Down == keyCode &&
		!paused)
	{
		// MOVE DOWN
		player->updateMovement(1);
	}
	else if (sf::Keyboard::Tab == keyCode &&
		!paused)
	{
		updateGameSpeed(10.f);
		player->updateScore(10.f);
		objects.clear();
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
	frequency = -650.f / (speed);
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

		if (background.getPosition().x + background.getSize().x < -background.getSize().x)
			background.move(sf::Vector2f(3.f * renderWindow->getSize().x, 0.f));
		if (background.getPosition().x > 2 * background.getSize().x)
			background.move(sf::Vector2f(-3.f * renderWindow->getSize().x, 0.f));
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

void GameState::updateCollision(Object* object)
{
	switch (object->type)
	{
	case Obstacle:
		//implement timer
		player->takeDamage();
		object->hit = true;
		if (player->getCurrentHealth() == 0) {
			togglePause(); //for now pausing the screen when player collides with cars 3 times
			leaderboard->addNewScore("default", player->getCurrentScore());
		}
		break;
	case Coin:
		player->gainCoin();
		break;
	default:
		break;
	}
}

//Collision Detection
void GameState::checkCollision() {
	if ((objects.front()->hit == false && CollisionDetection::PixelPerfectTest(player->getSprite(), objects.front()->getSprite())))
	{
		updateCollision(objects.front());
	}
	if (objects.size() > 1 && objects.at(1)->hit == false && CollisionDetection::PixelPerfectTest(player->getSprite(), objects.at(1)->getSprite()))
	{
		updateCollision(objects.at(1));
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