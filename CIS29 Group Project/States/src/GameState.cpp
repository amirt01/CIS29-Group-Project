#include "stdafx.h"
#include "GameState.h"
#include "CollisionDetection.h"
#include "SpawnError.h"
#include "TutorialState.h"

void GameState::restartState()
{
	currentState = PLAY;
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
	currentState(PLAY), buttons(nullptr), spawnTime(frequency),
	pauseMenu(renderWindow, &fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK")),
	deathMenu(renderWindow, &fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK")),
	winMenu(renderWindow, &fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK")),
	player(textures->at(gameStats->playerTexture), 104, 107),
	hud(&player, textures->at("HEART"), fonts->at("DOSIS-BOLD")),
	collide(textures->at("COLLISION")),
	backgroundMusic(soundBuffers->at("TECHNO_BACKGROUND"))
{
	for (int i = 0; i < backgrounds.size(); i++)
	{
		backgrounds[i].setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
			static_cast<float>(renderWindow->getSize().y)));
		backgrounds[i].setPosition(static_cast<float>(renderWindow->getSize().x * (i - 1.f)), 0.f);
		backgrounds[i].setTexture(&textures->at(gameStats->theme));
	}

	// Background Music Loop
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(25.f);
	backgroundMusic.play();
}

GameState::~GameState()
{
	objects.clear();
}

void GameState::spawnObject(unsigned short level, unsigned short type)
{
	try {
		switch (type)
		{
		case RED:
			objects.push_back(std::make_unique<Object>(Obstacle, level, textures->at("RED_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		case YELLOW:
			objects.push_back(std::make_unique<Object>(Obstacle, level, textures->at("YELLOW_CAR"), 280, 100, renderWindow->getSize().x));
			break;
		case ORANGE:
			objects.push_back(std::make_unique<Object>(Obstacle, level, textures->at("ORANGE_CAR"), 280, 100, renderWindow->getSize().x));
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
	case PLAY:
		switch (keyCode)
		{
		case sf::Keyboard::Escape:
			currentState = PAUSED;
			break;
		case sf::Keyboard::W:
			playSound("WOOSH", 25.f);
			player.updateMovement(-1);
			break;
		case sf::Keyboard::Up:
			playSound("WOOSH", 25.f);
			player.updateMovement(-1);
			break;
		case sf::Keyboard::S:
			playSound("WOOSH", 25.f);
			player.updateMovement(1);
			break;
		case sf::Keyboard::Down:
			playSound("WOOSH", 25.f);
			player.updateMovement(1);
			break;
		case sf::Keyboard::Tab:
			updateGameSpeed(10.f);
			player.updateScore(10.f);
			objects.clear();
			break;
		default:
			break;
		}
		break;
	case PAUSED:
		if (sf::Keyboard::Escape == keyCode)
			currentState = PLAY;
		break;
	case DEAD:
		switch (keyCode)
		{
		case sf::Keyboard::Escape:
			quitState();
			break;
		default:
			if (buttons != nullptr)
				buttons->at("NAME")->addText(keyCode);
		}
		break;
	case WIN:
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
	switch (currentState)
	{
	case PLAY:
		backgroundMusic.setVolume(25.f);
		buttons = nullptr;
		updateGameSpeed(deltaTime);
		updateBackground(deltaTime, FORWARDS);
		updateSpawning();
		player.updateScore(deltaTime);
		player.updateAnimation(deltaTime);
		hud.update();
		if (!objects.empty())
		{
			checkCollision();
			checkCarPassing();
			updateObjects(deltaTime);
		}
		break;
	case PAUSED:
		// do pause things
		backgroundMusic.setVolume(10.f);
		buttons = pauseMenu.getButtons();
		updateGUI();
		// Resume the Game
		if (buttons->at("RESUME")->getIsActivated())
			currentState = PLAY;
		//Go to Tutorial Screen
		if (buttons->at("TUTORIAL_STATE")->getIsActivated())
			states->push(std::make_unique<TutorialState>(renderWindow, states, textures, fonts, soundBuffers));

		// Quit This Game
		if (buttons->at("QUIT")->getIsActivated())
			quitState();

		break;
	case DEAD:
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
			quitState();
		}
		break;
	case WIN:
		// do win things
		sound.stop();
		buttons = winMenu.getButtons();
		updateGUI();
		// Restart Game
		if (buttons->at("RESTART")->getIsActivated())
			restartState();
		// Quit This Game
		if (buttons->at("QUIT")->getIsActivated())
			quitState();
		break;
	default:
		break;
	}
}

void GameState::updateCollision(std::unique_ptr<Object>& object)
{
	switch (object->type)
	{
	case Obstacle:
		playSound("CRASH", 50.f);
		player.takeDamage();
		object->hit = true;
		if (player.getCurrentHealth() == 0) { // render death menu if the player dies
			currentState = DEAD;
			deathMenu.setScore(player.getCurrentScore());
		}
		collide.collisionPosition(player.getCurrentPosition());
		player.collisionMove();
		break;
	case Coin:
		playSound("COIN", 50.f);
		player.gainCoin();
		break;
	default:
		break;
	}
}

//Collision Detection
void GameState::checkCollision() {
	if ((objects.front()->hit == false && CollisionDetection::PixelPerfectTest(player, *objects.front())))
	{
		updateCollision(objects.front());
	}
	if (objects.size() > 1 && objects.at(1)->hit == false && CollisionDetection::PixelPerfectTest(player, *objects.at(1)))
	{
		updateCollision(objects.at(1));
	}
}

void GameState::checkCarPassing()
{
	if (abs(objects.front()->getPosition().x - player.getPosition().x) < 100 && !objects.front()->hit)
	{
		if (player.passed(true))
		{
			playSound("CAR_PASSING", 25.f);
		}
	}
	else
	{
		player.passed(false); //reset boolean in player
	}
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
	case PLAY:
		break;
	case PAUSED:
		renderTarget->draw(pauseMenu);
		break;
	case DEAD:
		renderTarget->draw(deathMenu);
		break;
	case WIN:
		renderTarget->draw(winMenu);
		break;
	default:
		break;
	}

	if (collide.collisionTiming() &&
		!objects.empty())
		renderTarget->draw(collide);
}