#include "stdafx.h"
#include "Object.h"

Object::Object(short unsigned level, sf::Texture& texture, sf::IntRect intRect)
	: Entity()
{
	switch (level)
	{
	case TOP:
		sprite.setPosition(sf::Vector2f(1080.f, 250.f - (static_cast<float>(intRect.height) / 2.f)));
		break;
	case MIDDLE:
		sprite.setPosition(sf::Vector2f(1080.f, 375.f - (static_cast<float>(intRect.height) / 2.f)));
		break;
	case BOTTOM:
		sprite.setPosition(sf::Vector2f(1080.f, 525.f - (static_cast<float>(intRect.height) / 2.f)));
		break;
	default:
		break;
	}

	//initializeObjectImage();
	setTexture(texture, intRect);
}

int Object::getValue() {
	return value;
}

void Object::setValue(int v)
{
	value = v;
}

void Object::move(const float x, const float& deltaTime)
{
	sprite.move(sf::Vector2f(x, 0) * deltaTime);
}

//might not be needed
float Object::getCurrentPosition()
{
	return sprite.getPosition().x;
}

//might not be needed
void Object::setCurrentPosition(int cp)
{
	currentPosition = cp;
}

void Object::update(const float& deltaTime)
{
}