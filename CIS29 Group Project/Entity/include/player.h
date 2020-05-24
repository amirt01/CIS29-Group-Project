#pragma once
#include "Entity.h"

class player:public Entity {
protected:
	enum position {Up=0, Center=1, Down=2} pos;
	float movementShift;
	int currentPosition;
	int currentHealth;

public:
	player(sf::Texture texture);
	//Collision getCollision();
	
	void initializePlayerImage();
	void update();
	void updateMovement();
	bool checkPosition(int);

	void setCurrentHealth(int);
	int getCurrentHealth();
	void setMovementShift(float);
	float getMovementShift();
	void setCurrentPosition(int);
	int getCurrentPosition();
	void setPosition(position);
	position getPosition() const;
};