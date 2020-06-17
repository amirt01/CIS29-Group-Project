#pragma once

#include "Entity.h"
enum class JumpStates { NONE = 0, ASCEND, DESCEND };
enum class Directions { UP = -1, DOWN = 1, JUMP = 2 };

class Player : public Entity
{
private:
	// movement
	int moveType[2];
	std::array<float, 3> positions;
	float movementShift;
	int currentHealth;
	float score;
	float coins;

	bool isPassing;
	bool isJumping;
	float jumpHeight;
	JumpStates jumpState;

	sf::RenderTexture renderTexture;

	sf::Texture characterTexture;
	sf::Texture bikeTexture;
	sf::Texture wheelTexture;

	sf::Color playerColor;

public:
	Player(sf::Texture& playerTexture, float coins, std::array<float, 3> positions, const int width, const int height);
	Levels currentPosition;
	bool isDamaged;

	//update
	void updateMovement(Directions);
	void updateScore(const float& deltaTime);
	void updateAnimation(const float& deltaTime);

	//coins
	void gainCoin();
	unsigned int getCoins();

	//player health
	void takeDamage();
	void setCurrentHealth(int);
	int getCurrentHealth();
	void collisionMove(); // player auto moves
	void playerDamage(); // player transparency
	void revertPlayer();
	void resetPlayer();

	//Score
	float getCurrentScore();

	//position and movement
	bool checkPosition(Directions);
	void setMovementShift(float);
	float getMovementShift();
	void setCurrentPosition(int);
	int getCurrentPosition();
	bool getIsJumping();
	void nowJumping(float, float);

	//passing
	bool passed(bool);
};