#pragma once
#include "Entity.h"
#include "Player.h"
#include <array>

class Collide : public Entity
{
	sf::Clock clock;
	std::array<float, 3> positions;
public:
	Collide(sf::Texture& texture, std::array<float, 3> positions);
	void collisionPosition(int position, int player);
	bool collisionTiming();
};