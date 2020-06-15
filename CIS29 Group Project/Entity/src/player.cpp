#include "stdafx.h"
#include "player.h"

Player::Player(sf::Texture& playerTexture, const int width, const int height)
	: Entity(), moveType{ -1,1 },
	positions{ 170,300,431 },
	movementShift(130), //shift space (distance between lanes)
	currentPosition(Levels::MIDDLE), //pos = Center/1
	currentHealth(3), //3 being full health
	score(0),
	coins(0),
	isDamaged(false),
	isPassing(false),
	isJumping(false),
	jumpHeight(120),
	jumpState(jumpStates::NONE)
{
	setTexture(playerTexture);

	if (playerTexture.getSize().x > 200) {
		setTextureRect(sf::IntRect(0, 0, width, height));
		addAnimation("WHEELS", 0.1f, 0, 4, width, height);
	} else {
		addAnimation("WHEELS", 0.1f, 0, 1, 191, 107);
	}

	sf::Sprite::setPosition(sf::Vector2f(100, 300));
	playerColor = getColor();
}

void Player::updateScore(const float& deltaTime) 
{
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

	if (currentPosition == Levels::MIDDLE)
		updateMovement(1);
	else if (currentPosition == Levels::BOTTOM)
		updateMovement(-1);
}

void Player::collisionMove()
{
	switch (currentPosition)
	{
	case Levels::TOP:
		updateMovement(moveType[1]);
		break;
	case Levels::MIDDLE:
		updateMovement(moveType[static_cast<int>(rand() % sizeof(moveType))]);
		break;
	case Levels::BOTTOM:
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

void Player::updateMovement(int shift) 
{
	auto currentPos = getCurrentPosition();

	if (shift == -1) 
	{
		if (checkPosition(-1) && !isJumping)
		{
			move(sf::Vector2f(0, -movementShift));
			setCurrentPosition(currentPos - 1);
		}
	}
	else if (shift == 1) 
	{
		if (checkPosition(1) && !isJumping) 
		{
			move(sf::Vector2f(0, movementShift));
			setCurrentPosition(currentPos + 1);
		}
	}
	else if (shift == 2)
	{
		int moving = 0;
		if (!isJumping)
		{
			isJumping = true;
			jumpState = jumpStates::ASCEND;
		}
	}
}

void Player::nowJumping(float speed, float deltaTime, bool carPresent, bool passedCar)
{
	float moving = 0;
	int i = getCurrentPosition();

	switch (jumpState)
	{
	case jumpStates::NONE:
		moving = positions[i];
		break;
	case jumpStates::ASCEND:
		if (!carPresent && abs(getPosition().y - positions[i]) > jumpHeight)
		{
			moving = positions[i] - jumpHeight;
			jumpState = jumpStates::DESCEND;
		}
		else if (!carPresent)
		{
			moving = getPosition().y + 5*(speed * deltaTime);
		}
		else if (abs(getPosition().y - positions[i]) > jumpHeight)
		{
			moving = positions[i] - jumpHeight;
			jumpState = jumpStates::SUSPEND;
		}
		else
		{
			moving = getPosition().y + (speed * deltaTime);
		}
		break;
	case jumpStates::SUSPEND:
		moving = getPosition().y;
		if(passedCar)
		{
			jumpState = jumpStates::DESCEND;
		}
		break;
	case jumpStates::DESCEND:
		if (getPosition().y - positions[i] > 0)
		{
			moving = positions[i];
			jumpState = jumpStates::NONE;
			isJumping = false;
		}
		else if (!carPresent)
		{
			moving = getPosition().y - 3*(speed * deltaTime);
		}
		else
		{
			moving = getPosition().y - ((speed * deltaTime) / 2);
		}
		break;
	}

	setPosition(sf::Vector2f(getPosition().x, moving));
}


bool Player::getIsJumping()
{
	return isJumping;
}

bool Player::checkPosition(int direction) 
{
	if (direction == -1) {
		//wants to move up
		return currentPosition != Levels::TOP;
	}
	else if (direction == 1) {
		//wants to move down
		return currentPosition != Levels::BOTTOM;
	}
	else
	{
		return false; //temp
	}
}

void Player::takeDamage() 
{
	currentHealth -= 1;
}

//Getters and Setters
void Player::setCurrentHealth(int i)
{
	currentHealth = i;
}

int Player::getCurrentHealth() 
{
	return currentHealth;
}

float Player::getCurrentScore()
{
	return score;
}

void Player::setMovementShift(float i) 
{
	movementShift = i;
}

float Player::getMovementShift() 
{
	return movementShift;
}
void Player::setCurrentPosition(int i) 
{
	switch (i)
	{
	case 0:
		currentPosition = Levels::TOP;
		break;
	case 1:
		currentPosition = Levels::MIDDLE;
		break;
	case 2:
		currentPosition = Levels::BOTTOM;
		break;
	}
}

int Player::getCurrentPosition()
{
	int i = 0;
	switch (currentPosition)
	{
	case Levels::TOP:
		i = 0;
		break;
	case Levels::MIDDLE:
		i = 1;
		break;
	case Levels::BOTTOM:
		i = 2;
		break;
	}
	return i;
}

bool Player::passed(bool pass)
{
	if (pass && isPassing)
	{
		return false;
	}
	else if (pass && !isPassing)
	{
		isPassing = true;
		return true;
	}
	else
	{
		isPassing = false;
		return false;
	}
}