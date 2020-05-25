#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(unsigned short level, sf::Texture& texture, sf::IntRect intRect)
	: Object(level, texture)
{
	this->animationComponent->addAnimation("IDLE", 1.f, 0, 0, 8, 0, 32, 32);
}

Obstacle::~Obstacle()
{
}
