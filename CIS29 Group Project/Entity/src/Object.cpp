#include "stdafx.h"
#include "Object.h"

Object::Object(short unsigned level, sf::Texture& texture)
	: Entity(texture)
{
	std::cout << level << std::endl;

	switch (level)
	{
	case TOP:
		sprite.setPosition(sf::Vector2f(1080.f, 300.f));
		break;
	case MIDDLE:
		sprite.setPosition(sf::Vector2f(1080.f, 450.f));
		break;
	case BOTTOM:
		sprite.setPosition(sf::Vector2f(1080.f, 600.f));
		break;
	default:
		break;
	}

	//initializeObjectImage();
	sprite.setTexture(texture);
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