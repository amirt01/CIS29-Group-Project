#include "stdafx.h"
#include "Enemy.h"

//Initializer functions
void Enemy::initVariables()
{
}

//Constructors / Destructors
Enemy::Enemy(float x, float y, float maxVelocity, Player* player, sf::Texture& texture)
{
	initVariables();

	this->player = player;
	this->maxVelocity = maxVelocity;

	setTexture(texture);
	setPosition(x, y);
}

Enemy::~Enemy()
{

}

void Enemy::move(const float x, const float& deltaTime)
{
	velocity.x = maxVelocity * x;
}

void Enemy::update(const float& deltaTime)
{
	if (sprite.getPosition() == player->getPosition())
	{
		std::cout << "HIT!!!";
		system("PAUSE");
	}

	sprite.move(velocity * deltaTime);

	std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
	std::cout << player->getPosition().x << " " << player->getPosition().y << std::endl;

	if (sprite.getPosition().y == player->getPosition().y &&
		sprite.getPosition().x <= player->getPosition().x + 50.f)
	{
		std::cout << "HIT!!!";
		system("PAUSE");
	}
}