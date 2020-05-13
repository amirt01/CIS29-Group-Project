#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	level = MIDDLE;
}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture)
{
	initVariables();

	setTexture(texture);
	setPosition(x, y);
}

Player::~Player()
{

}

const sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

void Player::move(const short int direction)
{
	if (direction == UP)
	{
		switch (level)
		{
		case(TOP):
			break;

		case(MIDDLE):
			setPosition(20.f, 170.f);
			level = TOP;
			break;

		case(BOTTOM):
			setPosition(20.f, 310.f);
			level = MIDDLE;
			break;

		default:
			break;
		}	
	}
	else
	{
		switch (level)
		{
		case(TOP):
			setPosition(20.f, 310.f);
			level = MIDDLE;
			break;

		case(MIDDLE):
			setPosition(20.f, 450.f);
			level = BOTTOM;
			break;

		case(BOTTOM):
			break;

		default:
			break;
		}
	}
}

void Player::update()
{
}
