#pragma once

#include "Player.h"
#include "Entity.h"

class HUD
{
private:
	Player* player;

	std::array<Entity, 3> hearts;

	// Initializers
	void initializeHearts(sf::Texture& heartTexture);

public:
	HUD(Player* player, sf::Texture& heartTexture);
	~HUD();

	void update();
	void render(sf::RenderTarget* renderTarget);
};


