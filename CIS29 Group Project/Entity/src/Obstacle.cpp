#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(unsigned short level, sf::Texture& texture, sf::IntRect intRect)
	: Object(level, texture, intRect)
{
}

Obstacle::~Obstacle()
{
}
