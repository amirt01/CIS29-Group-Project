#pragma once

#include "State.h"
#include "PauseState.h"
#include "Object.h"
#include "Player.h"
#include "HUD.h"
#include "Collide.h"

enum color { Red = 0, Yellow, Orange };
enum obsticle { MEDIUM = 0, LARGE, SMALL };

class GameState : public State
{
private:
	float speed;
	bool paused;
	bool collision;

	PauseState pauseState;
	std::map<std::string, gui::Button*> buttons;

	Player* player;
	HUD* hud;
	Collide* collide;

	std::stack<State*>* states;
	std::array<sf::RectangleShape, 2> backgrounds;

	void togglePause();

	// Initializers
	void initializeTextures();

protected:
	float frequency;
	float spawnTime;

	std::deque<Object*> objects;

	virtual void updateSpawning() = 0;

public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~GameState();

	void spawnPlayer();
	void spawnObject(unsigned short level, unsigned short type);

	// Update
	void updateGUI();
	void updateInput(unsigned short keyCode);
	void updateGameSpeed(const float& deltaTime);
	void updateObjects(const float& deltaTime);
	void updateBackground(const float& deltaTime);
	void updateState(const float& deltaTime);

	//Collision Detection
	void checkCollision();

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};