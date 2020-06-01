#pragma once
#ifndef CollisionDetection_H
#define CollisionDetection_H
#include "stdafx.h"
//PixelPerfectTest comes form SonarSystem's code

namespace CollisionDetection {
	class BitmaskManager
	{
		std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
	public:
		~BitmaskManager();
		sf::Uint8 getPixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y);
		sf::Uint8* getMask(const sf::Texture* tex);
		sf::Uint8* createMask(const sf::Texture* tex, const sf::Image& img);
	};

	bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);
	bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
}

#endif // !CollisionDetection_H
