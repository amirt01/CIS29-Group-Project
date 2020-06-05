#pragma once

#include "State.h"
#include "PauseState.h"
#include "Object.h"
#include "Player.h"
#include "HUD.h"
#include "Leaderboard.h"
#include "Collide.h"

enum color { RED = 0, YELLOW, ORANGE };
enum obsticle { MEDIUM = 0, LARGE, SMALL };
enum direction { FORWARDS = 1, BACKWARDS = -1 };

class GameState : public State
{
private:
	float speed;
	bool paused;
	bool collision;

	PauseState pauseState;
	std::map<std::string, gui::Button*> buttons;

	Leaderboard* leaderboard;
	Player* player;
	HUD* hud;
	Collide* collide;

	std::stack<State*>* states;
	std::array<sf::RectangleShape, 3> backgrounds;

	void togglePause();

protected:
	float frequency;
	float spawnTime;

	std::deque<Object*> objects;

	// Initializers
	void initializeTextures();

	virtual void updateSpawning() = 0;

public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states, Leaderboard* leaderboard = nullptr);
	virtual ~GameState();

	void spawnPlayer();
	void spawnObject(unsigned short level, unsigned short type);

	// Update
	void updateGUI();
	virtual void updateKeyboard(unsigned short keyCode);
	void updateMouseWheel(short mouseDelta);
	void updateGameSpeed(const float& deltaTime);
	void updateObjects(const float& deltaTime);
	virtual void updateBackground(const float& deltaTime, const short dir = FORWARDS);
	virtual void updateState(const float& deltaTime);
	void updateCollision(Object* object);

	//Collision Detection
	void checkCollision();

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};