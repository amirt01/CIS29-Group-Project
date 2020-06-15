#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "DeathMenu.h"
#include "Player.h"
#include "Leaderboard.h"
#include "Collide.h"
#include "HUD.h"
#include "Object.h"
#include "WinMenu.h"
#include "GameStats.h"

enum Color { RED = 0, YELLOW, ORANGE, GOLD, CONVERTIBLE };
enum Obsticle { MEDIUM = 0, LARGE, SMALL };
enum Direction { FORWARDS = 1, BACKWARDS = -1 };
enum GameStates { PLAY = 0, PAUSED, DEAD, WIN };

class GameState : public State
{
private:
	float speed;

	PauseMenu pauseMenu;
	DeathMenu deathMenu;
	WinMenu winMenu;
	const std::map<std::string, std::unique_ptr<gui::Button>>* buttons;

	Leaderboard* leaderboard;
	GameStats* gameStats;

	sf::Sound backgroundMusic;

	std::stack<std::unique_ptr<State>>* states;
	std::array<sf::RectangleShape, 3> backgrounds;

protected:
	GameStates currentState;

	float frequency;
	float spawnTime;

	Player player; 
	HUD hud;
	Collide collide;

	std::deque<std::unique_ptr<Object>> objects;

	sf::Text coinAmount;

	// Initializers
	virtual void updateSpawning() = 0;
	virtual void restartState();

public:
	// Constructors/Destructors
	GameState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard, GameStats* gameStats);
	virtual ~GameState();

	void spawnObject(const Levels level, const Color color);

	// Update
	void updateGUI();
	void updateMouseButtons(const sf::Mouse::Button& button);
	virtual void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateMouseWheel(const short& mouseDelta);
	void updateGameSpeed(const float& deltaTime);
	void updateObjects(const float& deltaTime);
	virtual void updateBackground(const float& deltaTime, const Direction dir = Direction::FORWARDS);
	virtual void updateState(const float& deltaTime);
	void updateCollision(std::unique_ptr<Object>& object);
	void checkCarPassing();

	// Collision Detection
	void checkCollision();

	// Render
	void renderState(std::shared_ptr<sf::RenderTarget> renderTarget);
};