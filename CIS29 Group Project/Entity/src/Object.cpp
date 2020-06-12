#include "stdafx.h"
#include "Object.h"

Object::Object(const Type type, const short unsigned level, sf::Texture& texture, const int width, const int height, const int startingLocation)
	: Entity(), hit(false), type(type)
{
	switch (level)
	{
	case TOP:
		sprite.setPosition(sf::Vector2f(static_cast<float>(startingLocation + width), 200.f - static_cast<float>(height / 2)));
		break;
	case MIDDLE:
		sprite.setPosition(sf::Vector2f(static_cast<float>(startingLocation + width), 335.f - static_cast<float>(height / 2)));
		break;
	case BOTTOM:
		sprite.setPosition(sf::Vector2f(static_cast<float>(startingLocation + width), 460.f - static_cast<float>(height / 2)));
		break;
	default:
		break;
	}

	//initializeObjectImage();
	setTexture(texture);

	// MAKE SURE TO CREATE VARIABLES LATER
	addAnimation("IDLE", 0.1f, 0, 7, width, height);
}

int Object::getValue() {
	return value;
}

const float Object::getWidth() const
{
	return sprite.getGlobalBounds().width;
}

void Object::setValue(int v)
{
	value = v;
}

//might not be needed
float Object::getCurrentPosition()
{
	return sprite.getPosition().x;
}

void Object::updateAnimation(const float& deltaTime)
{
	animations["IDLE"]->update(deltaTime);
	sprite.setTextureRect(animations["IDLE"]->textureRect);
}

void Object::move(const float x, const float& deltaTime)
{
	sprite.move(sf::Vector2f(x, 0) * deltaTime);
}

void Object::update(const float& deltaTime)
{
	updateAnimation(deltaTime);
}