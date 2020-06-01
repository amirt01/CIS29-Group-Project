#pragma once
#include "Object.h"

class Coin : public Object
{
	Coin(unsigned short level, sf::Texture& texture, int width, int height);
	~Coin();
};

