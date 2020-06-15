#include "stdafx.h"
#include "Object.h"

Object::Object(const Type type, const Levels level, sf::Texture& texture, const int width, const int height, const int startingLocation)
	: Entity(), hit(false), type(type), value(1)
{
	switch (level)
	{
	case Levels::TOP:
		setPosition(sf::Vector2f(static_cast<float>(startingLocation + width), 200.f - static_cast<float>(height / 2)));
		break;
	case Levels::MIDDLE:
		setPosition(sf::Vector2f(static_cast<float>(startingLocation + width), 335.f - static_cast<float>(height / 2)));
		break;
	case Levels::BOTTOM:
		setPosition(sf::Vector2f(static_cast<float>(startingLocation + width), 460.f - static_cast<float>(height / 2)));
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