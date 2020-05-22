#pragma once

#include "State.h"
#include "PauseState.h"
#include "Obstacle.h"

enum type { OBSTICLE = 0, COIN };

class GameState :
	public State
{
protected:
	PauseState pauseState;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, sf::Texture> textures;
	std::deque<Object*> objects;
	void togglePause();

	std::stack<State*>* states;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	// Initializers
	void initializeBackground();
public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~GameState();

	void spawnObject(short unsigned level, short unsigned type);

	// Update
	void updateGUI();
	void updateInput(unsigned short keyCode);
	void updateObjects(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};