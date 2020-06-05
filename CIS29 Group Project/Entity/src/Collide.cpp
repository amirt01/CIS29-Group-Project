#include "stdafx.h"
#include "Collide.h"

Collide::Collide(sf::Texture& texture) :
	Entity()
{
	setTexture(texture);
	clock.restart();
}

void Collide::collisionPosition(int position)
{
	//player position is passed (0,1,2)
	switch (position)
	{
	case 0:
		sprite.setPosition(sf::Vector2f(80, 170));
		break;
	case 1:
		sprite.setPosition(sf::Vector2f(80, 300));
		break;
	case 2:
		sprite.setPosition(sf::Vector2f(80, 430));
		break;
	}
	clock.restart();
}

bool Collide::collisionTiming()
{
	if (clock.getElapsedTime().asMilliseconds() < 100) {
		return true;
	}
	else
	{
		return false;
	}
}

void Collide::playaudio(int i)
{
	switch (i)
	{

	case 0:
		//obstacle collide
		if (!soundBuffer.loadFromFile("Resources/Audio/crash2.wav"))
		{
			std::cout << "Sound didn't load" << std::endl; //temp
		}
		break;
	case 1:
		//coin
		if (!soundBuffer.loadFromFile("Resources/Audio/coin.wav"))
		{
			std::cout << "Sound didn't load" << std::endl; //temp
		}
		break;
	}

	sound.setBuffer(soundBuffer);
	sound.setVolume(20);
	sound.play();
}


