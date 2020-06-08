#include "stdafx.h"
#include "GameState.h"
#include "CollisionDetection.h"
#include "ExceptionHandler.h"
#include "TutorialState.h"

const std::map<const std::string, const std::string> TEXTRUE_PATHS =
{
	{"DEFAULT_PLAYER", "Resources/Images/motorbiker.png"},
	{"BLUE_PLAYER", "Resources/Images/motorbiker-blue.png"},
	{"RED_CAR", "Resources/Images/CarFramesRed.png"},
	{"YELLOW_CAR", "Resources/Images/CarFramesYellow.png"},
	{"ORANGE_CAR", "Resources/Images/CarFramesOrange.png"},
	{"BACKGROUND", "Resources/Images/GameBackground.png"},
	{"HEART", "Resources/Images/Heart.png"},
	{"COLLISION", "Resources/Images/CrashCartoon.png"}
};

//Initializers
void GameState::initializeTextures()
{
	for (auto& kv : TEXTRUE_PATHS)
		if (!textures[kv.first].loadFromFile(kv.second))
			exit(EXIT_FAILURE); // the loadFromFile() function has an ouput
								// when it fails so no need to throw
}

// Constructors/Destructors
GameState::GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states, Leaderboard* leaderboard)
	: State(renderWindow, states), leaderboard(leaderboard), speed(-75), frequency(5), states(states),
	currentState(PLAY), buttons(nullptr), spawnTime(frequency),
	pauseMenu(renderWindow), deathMenu(renderWindow)
{
	initializeTextures();
	initializeSounds();

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
	player = new Player(textures.at("BLUE_PLAYER"), 104, 107);
	hud = new HUD(player, textures.at("HEART"));
	collide = new Collide(textures.at("COLLISION"));
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
			throw exc::SpawnError(level, type);
			break;
		}
	}
	catch (exc::SpawnError& error)
	{
		std::cout << error.what();
		exit(EXIT_FAILURE);
	}
}

/* Functions */
// Update
void GameState::updateGUI()
{
	if (buttons != nullptr)
	{
		/*Updates all the buttons in the state and handles their functionality*/
		for (auto& it : *buttons) {
			it.second->updateColor(mousePosView);
		};
	}

	switch (currentState)
	{
	case PLAY:
		buttons = nullptr;
		break;
	case PAUSED:
		// Resume the Game
		if (buttons->at("RESUME")->getIsActivated())
			currentState = PLAY;

		//Go to Tutorial Screen
		if (buttons->at("TUTORIAL_STATE")->getIsActivated())
			states->push(new TutorialState(renderWindow, states));

		// Quit This Game
		if (buttons->at("QUIT")->getIsActivated())
			quitState();
		break;
	case DEAD:
		// Quit This Game
		if (buttons->at("QUIT")->getIsActivated())
			quitState();
		break;
	case WIN:
		break;
	default:
		buttons = nullptr;
		break;
	}
}

void GameState::updateMouseButtons(const sf::Mouse::Button& button)
{
	switch (button)
	{
	case sf::Mouse::Button::Left:
		if (buttons != nullptr)
			for (auto button : *buttons)
				button.second->checkBounds(mousePosView);
	default:
		break;
	}
}

void GameState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	if (sf::Keyboard::Escape == keyCode)
	{
		currentState = PAUSED;
	}

	if (sf::Keyboard::W == keyCode ||
		sf::Keyboard::Up == keyCode &&
		currentState == PLAY)
	{
		// MOVE UP
		player->updateMovement(-1);
	}
	else if (sf::Keyboard::S == keyCode ||
		sf::Keyboard::Down == keyCode &&
		currentState == PLAY)
	{
		// MOVE DOWN
		player->updateMovement(1);
	}
	else if (sf::Keyboard::Tab == keyCode &&
		currentState == PLAY)
	{
		updateGameSpeed(10.f);
		player->updateScore(10.f);
		objects.clear();
	}
}

void GameState::updateMouseWheel(const short& mouseDelta)
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
	updateMousePositions();
	updateGUI();
	switch (currentState)
	{
	case PLAY:
		updateGameSpeed(deltaTime);
		updateBackground(deltaTime, FORWARDS);
		updateSpawning();
		player->updateScore(deltaTime);
		player->updateAnimation(deltaTime);
		hud->update();
		if (!objects.empty())
		{
			checkCollision();
			updateObjects(deltaTime);
		}
		break;
	case PAUSED:
		buttons = pauseMenu.getButtons();
		break;
	case DEAD:
		break;
	case WIN:
		break;
	default:
		break;
	}
}

void GameState::updateCollision(Object* object)
{
	switch (object->type)
	{
	case Obstacle:
		playSound("CRASH", 50.f);
		player->takeDamage();
		object->hit = true;
		if (player->getCurrentHealth() == 0) { // render death menu if the player dies
			currentState = DEAD;
			buttons = deathMenu.getButtons();
			deathMenu.setScore(player->getCurrentScore());
			leaderboard->addNewScore("default", player->getCurrentScore());
		}
		collide->collisionPosition(player->getCurrentPosition());
		player->collisionMove();
		break;
	case Coin:
		playSound("COIN", 50.f);
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

	switch (currentState)
	{
	case PLAY:
		break;
	case PAUSED:
		renderTarget->draw(pauseMenu);
		break;
	case DEAD:
		renderTarget->draw(deathMenu);
		break;
	case WIN:
		break;
	default:
		break;
	}

	if (collide->collisionTiming())
		collide->render(renderTarget);
}