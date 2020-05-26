#include "stdafx.h"
#include "Object.h"

Object::Object(short unsigned level, sf::Texture& texture_sheet, int width, int height)
	: Entity()
{
	switch (level)
	{
	case TOP:
		sprite.setPosition(sf::Vector2f(1080.f, 250.f - static_cast<float>(height / 2)));
		break;
	case MIDDLE:
		sprite.setPosition(sf::Vector2f(1080.f, 375.f - static_cast<float>(height / 2)));
		break;
	case BOTTOM:
		sprite.setPosition(sf::Vector2f(1080.f, 525.f - static_cast<float>(height / 2)));
		break;
	default:
		break;
	}

	//initializeObjectImage();
	setTexture(texture_sheet);
}

int Object::getValue() {
	return value;
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

//might not be needed
void Object::setCurrentPosition(int cp)
{
	currentPosition = cp;
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