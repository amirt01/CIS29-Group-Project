#include "stdafx.h"
#include "player.h"

player::player(sf::Texture texture) :
	Entity(texture),
	pos(Center),
	movementShift(130), //shift space (distance between lanes)
	currentPosition(pos), //pos = Center/1
	currentHealth(2) //2 being full health
{	
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(50,350));
	resetClock();
	update();
}

void player::resetClock() {
	clock.restart();
}

int player::getTimeEllapsed() {
	return clock.getElapsedTime().asMilliseconds();
}

//Collision player::getCollision() {
//	return Collision(body);
//}

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
}

void player::updateMovement(int shift) {
	position currentPos = getPosition();

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
	else
	{
		return false; //temp
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