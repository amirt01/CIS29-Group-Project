#include "stdafx.h"
#include "player.h"

Player::Player(sf::Texture& playerTexture) :
	Entity(),
	moveType{-1,1},
	pos(Center),
	movementShift(130), //shift space (distance between lanes)
	currentPosition(pos), //pos = Center/1
	currentHealth(3), //3 being full health
	score(0),
	coins(0)
{

	setTexture(playerTexture);
	sprite.setPosition(sf::Vector2f(50, 300));
}

void Player::updateScore(const float& deltaTime) {
	score += deltaTime;
}

void Player::gainCoin()
{
	coins++;
}

unsigned int Player::getCoins()
{
	return coins;
}

void Player::collisionMove()
{
	switch (currentPosition)
	{
	case 0:
		updateMovement(moveType[1]);
		break;
	case 1:
		updateMovement(moveType[static_cast<int>(rand() % sizeof(moveType))]);
		break;
	case 2:
		updateMovement(moveType[0]);
		break;
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

void Player::takeDamage() {
	currentHealth -= 1;
}

//Getters and Setters
void Player::setCurrentHealth(int i) {
	currentHealth = i;
}

int Player::getCurrentHealth() {
	return currentHealth;
}

float Player::getCurrentScore()
{
	return score;
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