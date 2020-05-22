#pragma once
#include "Object.h"

class Obstacle : public Object
{
private:

public:
	Obstacle(unsigned short level, float maxVelocity, sf::Texture& texture);
	~Obstacle();
};

