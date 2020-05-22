#include "stdafx.h"
#include "Object.h"

Object::Object(short unsigned level, float maxVelocity, sf::Texture& texture)
	: Entity(texture)
{
	this->maxVelocity = maxVelocity;

	std::cout << level << std::endl;

	switch (level)
	{
	case TOP:
		sprite.setPosition(sf::Vector2f(100.f, 300.f));
		break;
	case MIDDLE:
		sprite.setPosition(sf::Vector2f(200.f, 300.f));
		break;
	case BOTTOM:
		sprite.setPosition(sf::Vector2f(300.f, 300.f));
		break;
	default:
		break;
	}

	system("PAUSE");

	//initializeObjectImage();
	sprite.setTexture(texture);
}

// Do this in Entity Class
//void Object::initializeObjectImage() {
//	if (!texture.loadFromFile("Resources/Images/star(temp object).png"))
//	{
//		std::cout << "object image cannot load" << std::endl;
//	}
//}
 
//void Object::updateMovement() {
//	//object moves toward left/player?
//
//	//movement code
//
//	update();
//}

int Object::getValue() {
	return value;
}

void Object::setValue(int v)
{
	value = v;
}

void Object::move(const float x, const float& deltaTime)
{
	velocity.x = maxVelocity * x;
}

//might not be needed
int Object::getCurrentPosition() {
	return sprite.getPosition().x;
}

//might not be needed
void Object::setCurrentPosition(int cp)
{
	currentPosition = cp;
}

void Object::update(const float& deltaTime)
{
	std::cout << "velocity :" <<  velocity.x << std::endl;
	sprite.move(velocity * deltaTime);
}