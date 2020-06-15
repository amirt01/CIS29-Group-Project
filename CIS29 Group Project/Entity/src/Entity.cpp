#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::addAnimation(const std::string key, float animation_time, int animation_level, int frames, int width, int height)
{
	animations[key] = std::make_unique<Animation>(
		animation_time,
		animation_level, frames, width, height
		);
}