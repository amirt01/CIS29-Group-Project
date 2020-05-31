#pragma once

#include "Entity.h"

class Player:public Entity {
protected:
	enum position { Up = 0, Center = 1, Down = 2 } pos;
	float movementShift;
	int currentPosition;
	int currentHealth;
	float score;

	sf::Clock clock;

public:
	Player(sf::Texture& playerTexture);
	
	// void update();
	void updateMovement(int);
	void updateScore(const float& deltaTime);

	bool checkPosition(int);

	void resetClock();
	int getTimeEllapsed();
	void takeDamage();
	void setCurrentHealth(int);
	int getCurrentHealth();

	float getCurrentScore();

	void setMovementShift(float);
	float getMovementShift();
	void setCurrentPosition(int);
	int getCurrentPosition();
	void setPosition(position);
	position getPosition() const;
};