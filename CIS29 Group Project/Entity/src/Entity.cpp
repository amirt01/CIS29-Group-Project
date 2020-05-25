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

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	animationComponent = new AnimationComponent(sprite, texture_sheet);
}

Entity::Entity()
{
}

Entity::~Entity()
{
	delete animationComponent;
}

void Entity::render(sf::RenderTarget* renderTarget)
{
	std::cout << sprite.getPosition().x << std::endl;
	renderTarget->draw(sprite);
}
