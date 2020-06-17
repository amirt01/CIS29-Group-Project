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
	Entity coinPic;
	sf::Texture coinTexture;
	sf::Font font;
	bool initializedCoins;

	// Initializers
	void initializeHearts(sf::Texture& heartTexture);
	void initializeContainer();
	void initializeScore(sf::Font& font);
	void initializeCoins(sf::Font& font, sf::Texture& coinTexture);


	float p2pXFactor;
	float p2pYFactor;

public:
	HUD(Player* player, sf::Texture& heartTexture, sf::Texture& coinTexture, sf::Font& font);
	~HUD();

	void update();
	void updateScore();
	void updateCoins();
	void render(std::shared_ptr<sf::RenderTarget> renderTarget);
};
