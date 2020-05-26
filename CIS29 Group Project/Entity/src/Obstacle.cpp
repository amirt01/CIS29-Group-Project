#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(unsigned short level, sf::Texture& texture_sheet, int width, int height)
	: Object(level, texture_sheet, width, height)
{
	// MAKE SURE TO CREATE VARIABLES LATER
	addAnimation("IDLE", 0.1f, 0, 7, width, height);
}

Obstacle::~Obstacle()
{
}
