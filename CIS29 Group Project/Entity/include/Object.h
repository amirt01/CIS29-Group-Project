#pragma once
#include "Entity.h"

class Object : public Entity
{
	int currentPosition; //might be unnecessary
	int value; //damage or pt value

public:
	Object(short unsigned level);
	void initializeObjectImage();
	void update();
	void updateMovement();

	int getCurrentPosition();
	int getValue();

	void setCurrentPosition(int);
	void setValue(int);
};