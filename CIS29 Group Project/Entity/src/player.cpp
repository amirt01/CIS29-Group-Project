#include "stdafx.h"
#include "player.h"

Player::Player(sf::Texture& texture) :
	Entity(),
	pos(Center),
	movementShift(130), //shift space (distance between lanes)
	currentPosition(pos), //pos = Center/1
	currentHealth(2) //2 being full health
{	
	setTexture(texture);
	sprite.setPosition(sf::Vector2f(50,300));
	resetClock();
	update();
}

void Player::resetClock() {
	clock.restart();
}

int Player::getTimeEllapsed() {
	return clock.getElapsedTime().asMilliseconds();
}

void Player::update() {
	if (currentPosition == 0) {
		setPosition(Up);
	}
	else if (currentPosition == 1) {
		setPosition(Center);
	}
	else if (currentPosition == 2) {
		setPosition(Down);
	}
}

void Player::updateMovement(int shift) {
	unsigned short currentPos = pos;

	if (shift == -1) {
		if (checkPosition(-1)) {
			sprite.move(sf::Vector2f(0, -movementShift));
			setCurrentPosition(currentPos - 1);
			clock.restart();
		}
	}
	else if (shift == 1) {
		if (checkPosition(1)) {
			sprite.move(sf::Vector2f(0, movementShift));
			setCurrentPosition(currentPos + 1);
			clock.restart();
		}
	}

	update(); //update sprite
}

bool Player::checkPosition(int direction) {
	if (direction == -1) {
		//wants to move up
		if (currentPosition != 0) {
			return true;
		}
		else { return false; }
	}
	else if (direction == 1) {
		//wants to move down
		if (currentPosition != 2) {
			return true;
		}
		else { return false; }
	}
	else
	{
		return false; //temp
	}
}

//Getters and Setters
void Player::setCurrentHealth(int i) {
	currentHealth = i;
}

int Player::getCurrentHealth() {
	return currentHealth;
}

void Player::setMovementShift(float i) {
	movementShift = i;
}

float Player::getMovementShift() {
	return movementShift;
}
void Player::setCurrentPosition(int i) {
	currentPosition = i;
}
int Player::getCurrentPosition() {
	return currentPosition;
}

void Player::setPosition(position x)
{
	pos = x;
}

Player::position Player::getPosition() const {
	return pos;
}