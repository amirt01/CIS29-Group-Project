#include "stdafx.h"
#include "Entity.h"

void Entity::setTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

Entity::Entity(sf::Texture& texture)
{
	setTexture(texture);
}

Entity::~Entity() {

}

void Entity::render(sf::RenderTarget* renderTarget)
{
	std::cout << sprite.getPosition().x << std::endl;
	renderTarget->draw(sprite);
}
