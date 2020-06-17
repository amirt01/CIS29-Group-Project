#include "stdafx.h"
#include "GameState.h"
#include "CollisionDetection.h"
#include "SpawnError.h"
#include "TutorialState.h"

void GameState::restartState()
{
	currentState = GameStates::PLAY;
	objects.clear();
	frequency = 5.f;
	spawnTime = frequency;
	speed = -75.f;
	player.resetPlayer();
}

// Constructors/Destructors
GameState::GameState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard, GameStats* gameStats)
	: State(renderWindow, states, textures, fonts, soundBuffers),
	leaderboard(leaderboard), states(states), gameStats(gameStats),
	speed(-75.f), frequency(5.f),
	currentState(GameStates::PLAY), level(0), buttons(nullptr), spawnTime(frequency),
	pauseMenu(renderWindow, &fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK")),
	deathMenu(renderWindow, &fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK")),
	winMenu(renderWindow, &fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK")),
	player(textures->at(gameStats->playerTexture), gameStats->coins, { p2pY(24.f), p2pY(42.f), p2pY(60.f) }, textures->at(gameStats->playerTexture).getSize().x / 4, textures->at(gameStats->playerTexture).getSize().y),
	hud(&player, textures->at("HEART"), textures->at("COIN"), fonts->at("DOSIS-BOLD")),
	collide(textures->at("COLLISION"), { p2pY(24.f), p2pY(42.f), p2pY(60.f) }),
	backgroundMusic(soundBuffers->at("TECHNO_BACKGROUND"))
{
	for (int i = 0; i < backgrounds.size(); i++)
	{
		backgrounds[i].setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
			static_cast<float>(renderWindow->getSize().y)));
		backgrounds[i].setPosition(static_cast<float>(renderWindow->getSize().x * (i - 1.f)), 0.f);
		backgrounds[i].setTexture(&textures->at(gameStats->theme));
	}

	player.setMovementShift(p2pY(18.f));

	// Background Music Loop
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(25.f);
	backgroundMusic.play();
}

GameState::~GameState()
{
	objects.clear();
	gameStats->coins = player.getCoins();
}

void GameState::spawnObject(const Levels level, const Color color)
{
	float pixLevel = 0.f;

	switch (level)
	{
	case Levels::TOP:
		pixLevel = p2pY(28.f);
		break;
	case Levels::MIDDLE:
		pixLevel = p2pY(46.5f);
		break;
	case Levels::BOTTOM:
		pixLevel = p2pY(64.f);
		break;
	default:
		break;
	}

	try {
		switch (color)
		{
		case Color::RED:
			objects.push_back(std::make_unique<Object>(Type::OBSTACLE, pixLevel, level, textures->at("RED_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		case Color::YELLOW:
			objects.push_back(std::make_unique<Object>(Type::OBSTACLE, pixLevel, level, textures->at("YELLOW_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		case Color::ORANGE:
			objects.push_back(std::make_unique<Object>(Type::OBSTACLE, pixLevel, level, textures->at("ORANGE_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		case Color::GOLD:
			objects.push_back(std::make_unique<Object>(Type::COIN, pixLevel, level, textures->at("COINS"), 128, 128, renderWindow->getSize().x));
			break;
		case Color::BLACK:
			objects.push_back(std::make_unique<Object>(Type::POTHOLE, pixLevel, level, textures->at("POTHOLE"), 115, 110, renderWindow->getSize().x));
			break;
		default:
			throw exc::SpawnError();
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
}

void GameState::updateMouseButtons(const sf::Mouse::Button& button)
{
	switch (button)
	{
	case sf::Mouse::Button::Left:
		if (buttons != nullptr)
			for (auto&& button : *buttons)
				button.second->checkBounds(mousePosView);
	default:
		break;
	}
}

void GameState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	switch (currentState)
	{
	case GameStates::PLAY:
		switch (keyCode)
		{
		case sf::Keyboard::Escape:
			currentState = GameStates::PAUSED;
			break;
		case sf::Keyboard::W:
			if (player.checkPosition(Directions::UP))
			{
				playSound("WOOSH", 25.f);
				player.updateMovement(Directions::UP);
			}
			break;
		case sf::Keyboard::Up:
			if (player.checkPosition(Directions::UP))
			{
				playSound("WOOSH", 25.f);
				player.updateMovement(Directions::UP);
			}
			break;
		case sf::Keyboard::S:
			if (player.checkPosition(Directions::DOWN))
			{
				playSound("WOOSH", 25.f);
				player.updateMovement(Directions::DOWN);
			}
			break;
		case sf::Keyboard::Down:
			if (player.checkPosition(Directions::DOWN))
			{
				playSound("WOOSH", 25.f);
				player.updateMovement(Directions::DOWN);
			}
			break;
		case sf::Keyboard::Tab:
			updateGameSpeed(10.f);
			player.updateScore(10.f);
			objects.clear();
			break;
		case sf::Keyboard::Space:
			if (level == 2 || level == 3) // disable jump
			{
				playSound("REVING", 20.f);
				player.updateMovement(Directions::JUMP);
			}
			break;
		default:
			break;
		}
		break;
	case GameStates::PAUSED:
		if (sf::Keyboard::Escape == keyCode)
			currentState = GameStates::PLAY;
		break;
	case GameStates::DEAD:
		switch (keyCode)
		{
		case sf::Keyboard::Escape:
			states->pop();
			break;
		default:
			if (buttons != nullptr)
				buttons->at("NAME")->addText(keyCode);
		}
		break;
	case GameStates::WIN:
		break;
	default:
		break;
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
	if (objects.front()->getPosition().x <= -objects.front()->getGlobalBounds().width)
	{
		objects.pop_front();
	}

	for (auto&& it : objects)
	{
		it->move(sf::Vector2f(speed, 0) * deltaTime);
		it->update(deltaTime);
	}
}

void GameState::updateBackground(const float& deltaTime, const BackgroundDirection dir)
{
	for (sf::RectangleShape& background : backgrounds) {
		background.move(2.f * speed * static_cast<float>(dir) * deltaTime, 0.f);

		if (background.getPosition().x + background.getSize().x < -background.getSize().x)
			background.move(sf::Vector2f(3.f * renderWindow->getSize().x, 0.f));
		if (background.getPosition().x > 2.f * background.getSize().x)
			background.move(sf::Vector2f(-3.f * renderWindow->getSize().x, 0.f));
	}
}

void GameState::updateState(const float& deltaTime)
{
	updateMousePositions();
	switch (currentState)
	{
	case GameStates::PLAY:
		backgroundMusic.setVolume(25.f);
		buttons = nullptr;
		updateGameSpeed(deltaTime);
		updateBackground(deltaTime, BackgroundDirection::FORWARDS);
		updateSpawning();
		player.updateScore(deltaTime);
		player.updateAnimation(deltaTime);
		hud.update();
		if (player.getIsJumping())
		{
			performJump(deltaTime);
		}

		if (!objects.empty())
		{
			checkCollision();
			checkCarPassing();
			updateObjects(deltaTime);
		}
		break;
	case GameStates::PAUSED:
		// do pause things
		backgroundMusic.setVolume(10.f);
		buttons = pauseMenu.getButtons();
		updateGUI();
		// Resume the Game
		if (buttons->at("RESUME")->getIsActivated())
			currentState = GameStates::PLAY;
		//Go to Tutorial Screen
		if (buttons->at("TUTORIAL_STATE")->getIsActivated())
			states->push(std::make_unique<TutorialState>(renderWindow, states, textures, fonts, soundBuffers));

		// Quit This Game
		if (buttons->at("QUIT")->getIsActivated())
			states->pop();

		break;
	case GameStates::DEAD:
		// do dead things
		sound.stop();
		buttons = deathMenu.getButtons();
		updateGUI();
		// Restart Game
		if (buttons->at("RESTART")->getIsActivated())
			restartState();
		// Quit This Game
		if (buttons->at("QUIT")->getIsActivated())
		{
			leaderboard->addNewScore(buttons->at("NAME")->getText(), player.getCurrentScore(), fonts->at("DOSIS-BOLD"));
			states->pop();
		}
		break;
	case GameStates::WIN:
		// do win things
		sound.stop();
		buttons = winMenu.getButtons();
		updateGUI();
		// Restart Game
		if (buttons->at("RESTART")->getIsActivated())
			restartState();
		// Quit This Game
		if (buttons->at("QUIT")->getIsActivated())
			states->pop();
		break;
	default:
		break;
	}
}

void GameState::updateCollision(std::unique_ptr<Object>& object)
{
	switch (object->type)
	{
	case Type::OBSTACLE:
		if (player.currentPosition != object->level && player.getIsJumping())
		{
			//do nothing
		}
		else
		{
			playSound("CRASH", 50.f);
			player.takeDamage();
			object->hit = true;
			if (player.getCurrentHealth() == 0) { // render death menu if the player dies
				currentState = GameStates::DEAD;
				deathMenu.setScore(player.getCurrentScore());
			}
			if (player.getTextureRect().width < 180)
			{
				// <180 being motorbike
				collide.collisionPosition(player.getCurrentPosition(), 0);
			}
			else
			{
				collide.collisionPosition(player.getCurrentPosition(), 1);
			}
			player.playerDamage();
		}
		break;
	case Type::COIN:
		playSound("COIN", 50.f);
		object->hit = true;
		player.gainCoin();

		for (auto it = objects.begin(); it != objects.end(); ++it) {
			if ((*it)->height == 128 && abs(player.getPosition().y - (*it)->getPosition().y) < 40) {
				objects.erase(it);
				it = objects.end() - 1;
			}
		}
		break;
	case Type::POTHOLE:
		//no damage but player "spins out" of current lane
		object->hit = true;
		if (!player.getIsJumping())
		{
			if (player.getTextureRect().width < 200)
			{
				collide.collisionPosition(player.getCurrentPosition(), 0);
			}
			else
			{
				collide.collisionPosition(player.getCurrentPosition(), 1);
			}
			playSound("SKID", 20.f);
			player.collisionMove();
		}
		break;
	default:
		break;
	}
}

//Collision Detection
void GameState::checkCollision()
{
	if (objects.empty())
	{
		return;
	}

	if ((objects.front()->hit == false && Collision::PixelPerfectTest(player, *objects.front())))
	{
		updateCollision(objects.front());
	}
	if (objects.size() > 1 && objects.at(1)->hit == false && Collision::PixelPerfectTest(player, *objects.at(1)))
	{
		updateCollision(objects.at(1));
	}

	if (objects.front()->hit == false && player.isDamaged)
	{
		player.revertPlayer();
	}
	else if (objects.front()->hit == true && player.currentPosition != objects.front()->level)
	{
		player.revertPlayer();
	}
	else if (objects.size() > 1 && objects.at(1)->hit == true && player.currentPosition != objects.front()->level)
	{
		player.revertPlayer();
	}

	if (objects.front()->hit == true && player.currentPosition == objects.front()->level && objects.front()->type == Type::OBSTACLE)
	{
		player.playerDamage();
	}
	if (objects.size() > 1 && objects.at(1)->hit == true && player.currentPosition == objects.at(1)->level && objects.at(1)->type == Type::OBSTACLE)
	{
		player.playerDamage();
	}
}

void GameState::checkCarPassing()
{
	if (abs(objects.front()->getPosition().x - player.getPosition().x) < 100 && !objects.front()->hit)
	{
		if (player.passed(true))
		{
			if (rand() % 2 == 0)
			{
				playSound("CAR_PASSING", 15.f);
			}
		}
	}
	else
	{
		player.passed(false); //reset boolean in player
	}
}

//Jumping

void GameState::performJump(const float& deltaTime)
{
	player.nowJumping(speed, deltaTime);
}

void GameState::setGameLevel(const int levelNumber)
{
	level = levelNumber;
}

// Render
void GameState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	//if (!renderTarget)
	//	renderTarget = renderWindow;

	for (int i = 0; i < backgrounds.size(); i++)
		renderTarget->draw(backgrounds[i]);

	for (auto&& it : objects)
		renderTarget->draw(*it);

	renderTarget->draw(player);
	hud.render(renderTarget);

	switch (currentState)
	{
	case GameStates::PLAY:
		break;
	case GameStates::PAUSED:
		renderTarget->draw(pauseMenu);
		break;
	case GameStates::DEAD:
		renderTarget->draw(deathMenu);
		break;
	case GameStates::WIN:
		renderTarget->draw(winMenu);
		break;
	default:
		break;
	}

	if (collide.collisionTiming() &&
		!objects.empty())
		renderTarget->draw(collide);
}