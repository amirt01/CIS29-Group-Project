#include "stdafx.h"
#include "Object.h"

Object::Object(const Type type, const float posY, const Levels level, sf::Texture& texture, const int width, const int height, const int startingLocation)
	: Entity(), hit(false), type(type), value(1), level(level), width(width), height(height)
{
	setPosition(sf::Vector2f(static_cast<float>(startingLocation + width), posY - static_cast<float>(height / 2)));

	setTexture(texture);

	// MAKE SURE TO CREATE VARIABLES LATER
	if (type == Type::OBSTACLE)
	{
		addAnimation("IDLE", 0.1f, 0, 7, width, height);
	}
	else if (type == Type::COIN)
	{
		addAnimation("IDLE", 0.1f, 0, 6, width, height);
	}
	else if (type == Type::POTHOLE)
	{
		addAnimation("IDLE", 0.1f, 0, 1, width, height);
	}
}

int Object::getValue() {
	return value;
}

void Object::setValue(int v)
{
	value = v;
}

void Object::updateAnimation(const float& deltaTime)
{
	animations["IDLE"]->update(deltaTime);
	setTextureRect(animations["IDLE"]->textureRect);
}

void Object::update(const float& deltaTime)
{
	updateAnimation(deltaTime);
}