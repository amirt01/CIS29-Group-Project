#pragma once

#include "Entity.h"

class Player:public Entity {
protected:
	enum position { Up = 0, Center = 1, Down = 2 } pos;
	float movementShift;
	int currentPosition;
	int currentHealth;

	sf::Clock clock;

public:
	Player(sf::Texture& playerTexture);
	
	void update();
	void updateMovement(int);
	bool checkPosition(int);

	void resetClock();
	int getTimeEllapsed();
	void takeDamage();
	void setCurrentHealth(int);
	int getCurrentHealth();
	void setMovementShift(float);
	float getMovementShift();
	void setCurrentPosition(int);
	int getCurrentPosition();
	void setPosition(position);
	position getPosition() const;
};