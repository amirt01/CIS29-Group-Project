#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "DeathMenu.h"
#include "Player.h"
#include "Leaderboard.h"
#include "Collide.h"
#include "HUD.h"
#include "Object.h"

enum Color { RED = 0, YELLOW, ORANGE };
enum Obsticle { MEDIUM = 0, LARGE, SMALL };
enum Direction { FORWARDS = 1, BACKWARDS = -1 };
enum GameStates { PLAY = 0, PAUSED, DEAD, WIN };

class GameState : public State
{
private:
	float speed;

	GameStates currentState;

	PauseMenu pauseMenu;
	DeathMenu deathMenu;
	const std::map<std::string, gui::Button*>* buttons;

	Leaderboard* leaderboard;
	Player* player;
	HUD* hud;
	Collide* collide;

	std::stack<State*>* states;
	std::array<sf::RectangleShape, 3> backgrounds;

protected:
	float frequency;
	float spawnTime;

	std::deque<Object*> objects;

	// Initializers
	virtual void updateSpawning() = 0;
	virtual void restartState();

public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard = nullptr);
	virtual ~GameState();

	void spawnPlayer();
	void spawnObject(unsigned short level, unsigned short type);

	// Update
	void updateGUI();
	void updateMouseButtons(const sf::Mouse::Button& button);
	virtual void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateMouseWheel(const short& mouseDelta);
	void updateGameSpeed(const float& deltaTime);
	void updateObjects(const float& deltaTime);
	virtual void updateBackground(const float& deltaTime, const short dir = FORWARDS);
	virtual void updateState(const float& deltaTime);
	void updateCollision(Object* object);

	// Collision Detection
	void checkCollision();

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};