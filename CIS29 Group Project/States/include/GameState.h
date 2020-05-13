#pragma once

#include "State.h"
#include "Enemy.h"
#include "Player.h"

class GameState :
	public State
{
protected:
	std::stack<State*>* states;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	std::map<std::string, sf::Texture> textures;

	Enemy* enemy;
	Player* player;

	// Initializers
	void initializePlayer();
	void initializeBackground();
	void initializeTextures();
public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~GameState();

	// Update
	void updateInput(unsigned short keyCode);
	void updateState(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};