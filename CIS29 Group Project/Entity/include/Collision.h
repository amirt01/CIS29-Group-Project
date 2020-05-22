#pragma once
#include "stdafx.h"

class Collision{

sf::RectangleShape body;

public:
	Collision(sf::RectangleShap&);
	~Collision();

	void move(float, float);
	bool checkCollision(Collision& , float);
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();
}