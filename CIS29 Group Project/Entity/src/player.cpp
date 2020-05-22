#include "stdafx.h"
#include "player.h"

player::player() :
	pos(Center),
	movementShift(200), //shift space (distance between lanes)
	currentPosition(pos), //pos = Center/1
	currentHealth(2) //2 being full health
{
	rect.setSize(sf::Vector2f(40.f, 40.f)); 
	rect.setPosition(sf::Vector2f(300.f, 335.f)); //placed in center lane
	rect.setFillColor(sf::Color::White);
	
	initializePlayerImage(); //current placeholder is 40px x 40px
	sprite.setTexture(texture);
	update();
}

Collision player::getCollision() {
	return Collision(body);
}

void player::initializePlayerImage() {
	if(!texture.loadFromFile("Resources/Images/redCircle(temp player).png"))
	{
		std::cout << "player image cannot load" << std::endl;
	}
}

void player::update() {
	if (currentPosition == 0) {
		setPosition(Up);
	}
	else if (currentPosition == 1) {
		setPosition(Center);
	}
	else if (currentPosition == 2) {
		setPosition(Down);
	}
	sprite.setPosition(rect.getPosition());
}

void player::updateMovement() {
	position currentPos = getPosition();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (checkPosition(-1)) {
			rect.move(sf::Vector2f(0, -movementShift)); //move into upper lane
			setCurrentPosition(currentPos - 1);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (checkPosition(1)) {
			rect.move(sf::Vector2f(0, movementShift)); //move into lower lane
			setCurrentPosition(currentPos + 1);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//leaving jumb empty for now
	}

	update(); //update sprite
}

bool player::checkPosition(int direction) {
	if (direction == -1) {
		//wants to move left
		if (currentPosition != 0) {
			return true;
		}
		else { return false; }
	}
	else if (direction == 1) {
		//wants to move right
		if (currentPosition != 2) {
			return true;
		}
		else { return false; }
	}
}

//Getters and Setters
void player::setCurrentHealth(int i) {
	currentHealth = i;
}

int player::getCurrentHealth() {
	return currentHealth;
}

void player::setMovementShift(float i) {
	movementShift = i;
}

float player::getMovementShift() {
	return movementShift;
}
void player::setCurrentPosition(int i) {
	currentPosition = i;
}
int player::getCurrentPosition() {
	return currentPosition;
}

void player::setPosition(position x)
{
	pos = x;
}

player::position player::getPosition() const {
	return pos;
}