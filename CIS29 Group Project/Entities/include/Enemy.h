#pragma once

#include "Entity.h"
#include "Player.h"

class Enemy :
	public Entity
{
private:
	//Variables
	float maxVelocity;
	Player* player;

	sf::Vector2f velocity;

	//Initializer functions
	void initVariables();

public:
	Enemy(float x, float y, float maxVelocity, Player* player, sf::Texture& texture);
	virtual ~Enemy();

	//Functions
	void move(const float x, const float& dt);
	void update(const float& dt);
};

