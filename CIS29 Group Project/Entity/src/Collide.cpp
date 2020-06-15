#include "stdafx.h"
#include "Collide.h"

Collide::Collide(sf::Texture& texture) :
	Entity(), positions{170.f,300.f,430.f}
{
	setTexture(texture);
	clock.restart();
}

void Collide::collisionPosition(int position, int player)
{
	//player position is passed (0,1,2)
	float x = 80;

	switch (player)
	{
	case 0:
		x = 80;
		break;
	case 1:
		x = 180;
		break;
	}
	setPosition(sf::Vector2f(x, positions[position]));
	clock.restart();
}

bool Collide::collisionTiming()
{
	return clock.getElapsedTime().asMilliseconds() < 100;
}