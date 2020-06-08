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
	sf::Text coins;

	// Initializers
	void initializeHearts(sf::Texture& heartTexture);
	void initializeContainer();
	void initializeScore(sf::Font& font);

public:
	HUD(Player* player, sf::Texture& heartTexture, sf::Font& font);
	~HUD();

	void update();
	void updateScore();
	void updateCoins();
	void render(sf::RenderTarget* renderTarget);
};
