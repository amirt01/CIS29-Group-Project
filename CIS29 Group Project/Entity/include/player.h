#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	enum position { Up = 0, Center = 1, Down = 2 } pos;
	int moveType[2];
	float movementShift;
	int currentPosition;
	int currentHealth;
	float score;
	unsigned int coins;
	bool isDamaged;

	sf::Texture playerTexture;
	sf::Color playerColor;
	sf::Clock clock;

public:
	Player(sf::Texture& playerTexture, const int width, const int height);

	//update
	void updateMovement(int);
	void updateScore(const float& deltaTime);
	void updateAnimation(const float& deltaTime);

	//coins
	void gainCoin();
	unsigned int getCoins();

	void resetPlayer();

	//player health
	void takeDamage();
	void setCurrentHealth(int);
	int getCurrentHealth();
	void collisionMove(); // player auto moves
	void playerDamage(); // player transparency
	void revertPlayer();

	//Score
	float getCurrentScore();

	//position and movement
	bool checkPosition(int);
	void setMovementShift(float);
	float getMovementShift();
	void setCurrentPosition(int);
	int getCurrentPosition();
	void setPosition(position);
	position getPosition() const;
};