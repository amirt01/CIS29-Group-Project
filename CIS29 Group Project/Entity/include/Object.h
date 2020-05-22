#pragma once
#include "Entity.h"

class Object : public Entity {
	int currentPosition; //might be unnecessary
	int value; //damage or pt value

public:
	Object();
	void initializeObjectImage();
	void update();
	void updateMovement();

	int getCurrentPosition();
	void setCurrentPosition(int);
	int getValue();
	void setValue(int);
};