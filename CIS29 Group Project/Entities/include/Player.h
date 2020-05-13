#pragma once

#include "Entity.h"

enum levels { BOTTOM = 0, MIDDLE, TOP };
enum direction { UP = 0, DOWN = 1 };

class Player :
	public Entity
{
private:
	//Variables
	unsigned short level;

	//Initializer functions
	void initVariables();

public:
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();

	const sf::Vector2f getPosition() const;

	//Functions
	void move(const short int direction);
	void update();
};
