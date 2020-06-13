#include "stdafx.h"
#include "player.h"

Player::Player(sf::Texture& playerTexture, const int width, const int height)
	: Entity(), moveType{ -1,1 },
	movementShift(130), //shift space (distance between lanes)
	currentPosition(1), //pos = Center/1
	currentHealth(3), //3 being full health
	score(0),
	coins(0),
	isDamaged(false)
{
	setTexture(playerTexture);
	setTextureRect(sf::IntRect(0, 0, width, height));

	addAnimation("WHEELS", 0.1f, 0, 4, width, height);

	sf::Sprite::setPosition(sf::Vector2f(50, 300));
	playerColor = getColor();
}

void Player::updateScore(const float& deltaTime) {
	score += deltaTime;
}

void Player::updateAnimation(const float& deltaTime)
{
	animations["WHEELS"]->update(deltaTime);
	setTextureRect(animations["WHEELS"]->textureRect);
}

void Player::gainCoin()
{
	coins++;
}

unsigned int Player::getCoins()
{
	return coins;
}

void Player::resetPlayer()
{
	score = 0.f;
	currentHealth = 3;
	coins = 0;

	if (currentPosition == 0)
		updateMovement(1);
	else if (currentPosition == 2)
		updateMovement(-1);
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

void Player::playerDamage()
{
	if (isDamaged) {
		setColor(playerColor);
		isDamaged = false;
	}
	else
	{
		setColor(sf::Color::Transparent);
		isDamaged = true;
	}
}

void Player::revertPlayer()
{
	if (isDamaged)
	{
		setColor(playerColor);
	}
}

void Player::updateMovement(int shift) {
	unsigned short currentPos = getCurrentPosition();

	if (shift == -1) {
		if (checkPosition(-1)) {
			move(sf::Vector2f(0, -movementShift));
			setCurrentPosition(currentPos - 1);
		}
	}
	else if (shift == 1) {
		if (checkPosition(1)) {
			move(sf::Vector2f(0, movementShift));
			setCurrentPosition(currentPos + 1);
		}
	}
}

bool Player::checkPosition(int direction) {
	if (direction == -1) {
		//wants to move up
		return currentPosition != 0;
	}
	else if (direction == 1) {
		//wants to move down
		return currentPosition != 2;
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

