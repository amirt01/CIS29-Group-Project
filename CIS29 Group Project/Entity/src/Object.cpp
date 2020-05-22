#include "stdafx.h"
#include "Object.h"

Object::Object(short unsigned level) {
	//value(5);

	rect.setSize(sf::Vector2f(30.f, 30.f));
	rect.setFillColor(sf::Color::Green);

	initializeObjectImage();
	sprite.setTexture(texture);
	update();
}

void Object::initializeObjectImage() {
	if (!texture.loadFromFile("Resources/Images/star(temp object).png"))
	{
		std::cout << "object image cannot load" << std::endl;
	}
}

void Object::update() {
	sprite.setPosition(rect.getPosition());
}

void Object::updateMovement() {
	//object moves toward left/player?

	//movement code

	update();
}

int Object::getValue() {
	return value;
}

void Object::setValue(int v)
{
	value = v;
}

//might not be needed
int Object::getCurrentPosition() {
	return currentPosition;
}

//might not be needed
void Object::setCurrentPosition(int cp)
{
	currentPosition = cp;
}