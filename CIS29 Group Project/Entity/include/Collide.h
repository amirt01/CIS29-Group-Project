#pragma once
#include "Entity.h"
#include "Player.h"
#include <array>

class Collide : public Entity
{
	sf::Clock clock;
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;
public:
	Collide(sf::Texture& texture);
	void collisionPosition(int position);
	bool collisionTiming();
	void playaudio(sf::SoundBuffer& soundBuffer);
};