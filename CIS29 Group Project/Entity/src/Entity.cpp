#include "stdafx.h"
#include "Entity.h"

void Entity::setTexture(sf::Texture& texture, sf::IntRect& intRect)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(intRect);
}

void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

Entity::Entity()
{
}

Entity::~Entity() {

}

void Entity::render(sf::RenderTarget* renderTarget)
{
	std::cout << sprite.getPosition().x << std::endl;
	renderTarget->draw(sprite);
}
