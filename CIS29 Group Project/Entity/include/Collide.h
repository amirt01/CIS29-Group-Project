#pragma once
#include "Entity.h"
#include "Player.h"

class Collide : public Entity
{
	sf::Clock clock;
public:
	Collide(sf::Texture& texture);
	void collisionPosition(int position);
	bool collisionTiming();
};