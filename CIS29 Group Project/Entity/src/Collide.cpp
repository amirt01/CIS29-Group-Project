#include "stdafx.h"
#include "Collide.h"

Collide::Collide(sf::Texture& texture, std::array<float, 3> positions) :
	Entity(), positions(positions)
{
	setTexture(texture);
	clock.restart();
}

void Collide::collisionPosition(int position, int player)
{
	float x = 0.f;

	switch (player)
	{
	case 0:
		x = 50.f;
		break;
	case 1:
		x = 150.f;
		break;
	}
	setPosition(sf::Vector2f(x, positions[position])); //player position is passed (0,1,2)
	clock.restart();
}

bool Collide::collisionTiming()
{
	return clock.getElapsedTime().asMilliseconds() < 100;
}