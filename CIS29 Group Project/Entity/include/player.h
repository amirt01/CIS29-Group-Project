#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	int moveType[2];
	int positions[3];
	float movementShift;
	int currentPosition;
	int currentHealth;
	float score;
	unsigned int coins;
	bool isDamaged;
	bool isPassing;
	bool isJumping;
	bool isAscending;
	bool isDescending;
	const float gravity;
	float jumpHeight;
	enum jumpStates {NONE = 0, ASCEND, SUSPEND, DESCEND};
	unsigned short jumpState;

	sf::RenderTexture renderTexture;

	sf::Texture characterTexture;
	sf::Texture bikeTexture;
	sf::Texture wheelTexture;

	sf::Color playerColor;

public:
	Player(sf::Texture& playerTexture, const int width, const int height);

	//update
	void updateMovement(int);
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
	bool checkPosition(int);
	void setMovementShift(float);
	float getMovementShift();
	void setCurrentPosition(int);
	int getCurrentPosition();
	bool getIsJumping();
	void nowJumping(float, float,bool);

	//passing
	bool passed(bool);
};