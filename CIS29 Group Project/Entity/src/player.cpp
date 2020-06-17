#include "stdafx.h"
#include "player.h"

Player::Player(sf::Texture& playerTexture, float coins, std::array<float, 3> positions, const int width, const int height)
	: Entity(), moveType{ -1,1 },
	positions(positions),
	movementShift(0),
	currentPosition(Levels::MIDDLE), //pos = Center/1
	currentHealth(3), //3 being full health
	score(0),
	coins(coins),
	isDamaged(false),
	isPassing(false),
	isJumping(false),
	jumpHeight(100),
	jumpState(JumpStates::NONE)
{
	setTexture(playerTexture);

	setTextureRect(sf::IntRect(0, 0, width, height));
	addAnimation("WHEELS", 0.1f, 0, 4, width, height);

	sf::Sprite::setPosition(sf::Vector2f(80, positions[1]));
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
	coins += 5;
}

unsigned int Player::getCoins()
{
	return coins;
}

void Player::resetPlayer()
{
	score = 0.f;
	currentHealth = 3;

	if (currentPosition == Levels::TOP)
		updateMovement(Directions::DOWN);
	else if (currentPosition == Levels::BOTTOM)
		updateMovement(Directions::UP);
	revertPlayer();
}

void Player::collisionMove()
{
	switch (currentPosition)
	{
	case Levels::TOP:
		updateMovement(Directions::DOWN);
		break;
	case Levels::MIDDLE:
		updateMovement(Directions::UP);
		break;
	case Levels::BOTTOM:
		updateMovement(Directions::UP);
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

void Player::updateMovement(Directions direction)
{
	auto currentPos = getCurrentPosition();

	switch (direction)
	{
	case Directions::UP:
		if (!isJumping)
		{
			move(sf::Vector2f(0, -movementShift));
			setCurrentPosition(currentPos - 1);
		}
		break;
	case Directions::DOWN:
		if (!isJumping)
		{
			move(sf::Vector2f(0, movementShift));
			setCurrentPosition(currentPos + 1);
		}
		break;

	case Directions::JUMP:
		if (!isJumping)
		{
			isJumping = true;
			jumpState = JumpStates::ASCEND;
		}
	default:
		break;
	}
}

void Player::nowJumping(float speed, float deltaTime)
{
	float moving = 0;
	int i = getCurrentPosition();

	switch (jumpState)
	{
	case JumpStates::NONE:
		moving = positions[i];
		break;
	case JumpStates::ASCEND:
		if (abs(getPosition().y - positions[i]) > jumpHeight)
		{
			moving = positions[i] - jumpHeight;
			jumpState = JumpStates::DESCEND;
		}
		else
		{
			moving = getPosition().y + (speed * deltaTime);
		}
		break;
	case JumpStates::DESCEND:
		if (getPosition().y - positions[i] > 0)
		{
			moving = positions[i];
			jumpState = JumpStates::NONE;
			isJumping = false;
		}
		else
		{
			moving = getPosition().y - (speed * deltaTime) / 1.5f;
		}
		break;
	}

	setPosition(sf::Vector2f(getPosition().x, moving));
}

bool Player::getIsJumping()
{
	return isJumping;
}

bool Player::checkPosition(Directions direction)
{
	switch (direction)
	{
	case Directions::UP:
		return currentPosition != Levels::TOP;
		break;
	case Directions::DOWN:
		return currentPosition != Levels::BOTTOM;
		break;
	default:
		return false;
		break;
	}
}

void Player::takeDamage()
{
	currentHealth -= 1;
	isDamaged = true;
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