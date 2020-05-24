#pragma once
#include "Object.h"

class Obstacle : public Object
{
private:

public:
	Obstacle(unsigned short level, sf::Texture& texture, sf::IntRect intRect);
	~Obstacle();
};

