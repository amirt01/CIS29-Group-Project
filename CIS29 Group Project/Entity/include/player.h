#pragma once
#include "Entity.h"

class player:public Entity {
protected:
	enum position {Up=0, Center=1, Down=2} pos;
	float movementShift;
	int currentPosition;
	int currentHealth;
	sf::Clock clock;

public:
	player(sf::Texture);
	//Collision getCollision();
	
	void update();
	void updateMovement(int);
	bool checkPosition(int);

	void resetClock();
	int getTimeEllapsed();
	void setCurrentHealth(int);
	int getCurrentHealth();
	void setMovementShift(float);
	float getMovementShift();
	void setCurrentPosition(int);
	int getCurrentPosition();
	void setPosition(position);
	position getPosition() const;
};