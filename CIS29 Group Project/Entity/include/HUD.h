#pragma once

#include "Player.h"
#include "Entity.h"

class HUD
{
private:
	sf::RectangleShape container;
	Player* player;

	std::array<Entity, 3> hearts;
	sf::Text score;

	sf::Font font;

	// Initializers
	void initializeHearts(sf::Texture& heartTexture);
	void initializeFonts();
	void initializeContainer();
	void initializeScore();

public:
	HUD(Player* player, sf::Texture& heartTexture);
	~HUD();

	void update();
	void updateScore();
	void render(sf::RenderTarget* renderTarget);
};


