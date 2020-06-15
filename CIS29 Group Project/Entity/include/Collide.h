#pragma once
#include "Entity.h"
#include "Player.h"
#include <array>

class Collide : public Entity
{
	sf::Clock clock;
	float positions[3];
public:
	Collide(sf::Texture& texture);
	void collisionPosition(int position, int player);
	bool collisionTiming();
};