#include "stdafx.h"
#include "Object.h"

Object::Object(Type type, short unsigned level, sf::Texture& texture_sheet, int width, int height)
	: Entity(), hit(false), type(type)
{
	switch (level)
	{
	case TOP:
		sprite.setPosition(sf::Vector2f(1080.f, 200.f - static_cast<float>(height / 2)));
		break;
	case MIDDLE:
		sprite.setPosition(sf::Vector2f(1080.f, 335.f - static_cast<float>(height / 2)));
		break;
	case BOTTOM:
		sprite.setPosition(sf::Vector2f(1080.f, 460.f - static_cast<float>(height / 2)));
		break;
	default:
		break;
	}

	//initializeObjectImage();
	setTexture(texture_sheet);

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