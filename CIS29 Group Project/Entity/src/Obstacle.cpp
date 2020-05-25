#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(unsigned short level, sf::Texture& texture_sheet, sf::IntRect intRect)
	: Object(level, texture_sheet)
{
	addAnimation("IDLE", 0.1f, 0, 7, 320, 320);
}

Obstacle::~Obstacle()
{
}
