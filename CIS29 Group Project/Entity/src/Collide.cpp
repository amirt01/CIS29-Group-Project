#include "stdafx.h"
#include "Collide.h"

Collide::Collide(sf::Texture& texture) :
	Entity()
{
	setTexture(texture);
	clock.restart();
}

void Collide::collisionPosition(int position)
{
	//player position is passed (0,1,2)
	switch (position)
	{
	case 0:
		sprite.setPosition(sf::Vector2f(80, 170));
		break;
	case 1:
		sprite.setPosition(sf::Vector2f(80, 300));
		break;
	case 2:
		sprite.setPosition(sf::Vector2f(80, 430));
		break;
	}
	clock.restart();
}

bool Collide::collisionTiming()
{
	if (clock.getElapsedTime().asMilliseconds() < 100) {
		return true;
	}
	else
	{
		return false;
	}
}

