#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(unsigned short level, float maxVelocity, sf::Texture& texture)
	: Object(level, maxVelocity, texture)
{
}

Obstacle::~Obstacle()
{
}
