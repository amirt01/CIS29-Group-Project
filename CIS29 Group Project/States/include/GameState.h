#pragma once

#include "State.h"
#include "PauseState.h"
#include "Obstacle.h"
#include "Player.h"
#include "HUD.h"

enum color { Red = 0, Yellow, Orange };
enum obsticle { MEDIUM = 0, LARGE, SMALL };

class GameState :
	public State
{
protected:
	float speed;
	float frequency;

	PauseState pauseState;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, sf::Texture> textures;
	std::deque<Object*> objects;

	Player* player;
	HUD* hud;

	std::stack<State*>* states;
	std::array<sf::RectangleShape, 2> backgrounds;
	//sf::RectangleShape background;
	sf::Texture backgroundTexture;

	void togglePause();

	// Initializers
	void initializeTextures();
public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~GameState();

	void spawnPlayer();
	void spawnObject(unsigned short level, unsigned short type);

	// Update
	void updateGUI();
	void updateInput(unsigned short keyCode);
	void updateObjects(const float& deltaTime);
	void updateBackground(const float& deltaTime);

	//Collision Detection
	void checkCollision();

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};