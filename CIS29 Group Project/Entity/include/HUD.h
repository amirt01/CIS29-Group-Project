#pragma once

#include "Player.h"

class HUD
{
private:
	sf::RectangleShape container;
	Player* player;

	std::array<Entity, 3> hearts;
	sf::Text score;
	sf::Text coins;
	sf::RectangleShape coinBackground;
	sf::RectangleShape coinPic;

	// Initializers
	void initializeHearts(sf::Texture& heartTexture);
	void initializeContainer();
	void initializeScore(sf::Font& font);
	void initializeCoins(sf::Font& font, sf::Texture& coinTexture);

public:
	HUD(Player* player, sf::Texture& heartTexture, sf::Texture& coinTexture, sf::Font& font);
	~HUD();

	void update();
	void updateScore();
	void updateCoins();
	void render(std::shared_ptr<sf::RenderTarget> renderTarget);
};
