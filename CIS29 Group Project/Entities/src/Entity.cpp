#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
}

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
