#include "stdafx.h"
#include "Entity.h"

void Entity::setTexture(sf::Texture& texture_sheet)
{
	sprite.setTexture(texture_sheet);
}

void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

Entity::Entity()
{
}

Entity::~Entity()
{
}

sf::Sprite Entity::getSprite()
{
	return sprite;
}

void Entity::addAnimation(const std::string key, float animation_time, int animation_level, int frames, int width, int height)
{
	animations[key] = new Animation(
		animation_time,
		animation_level, frames, width, height
	);
}

void Entity::render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(sprite);
}
