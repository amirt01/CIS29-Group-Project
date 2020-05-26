#pragma once
#include "Object.h"

class Obstacle : public Object
{
private:

public:
	Obstacle(unsigned short level, sf::Texture& texture, int width, int height);
	~Obstacle();
};

