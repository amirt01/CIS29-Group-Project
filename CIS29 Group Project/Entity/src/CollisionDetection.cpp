#include "stdafx.h"
#include "CollisionDetection.h"

CollisionDetection::BitmaskManager::~BitmaskManager()
{
	std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
	for (auto iterator = Bitmasks.begin(); iterator != end; iterator++)
	{
		delete[] iterator->second;
	}
}

sf::Uint8 CollisionDetection::BitmaskManager::getPixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y)
{
	if (x > tex->getSize().x || y > tex->getSize().y)
	{
		return 0;
	}
	return mask[x + y * tex->getSize().y];
}

sf::Uint8* CollisionDetection::BitmaskManager::getMask(const sf::Texture* tex)
{
	sf::Uint8* mask;
	auto pair = Bitmasks.find(tex);
	if (pair == Bitmasks.end()) 
	{
		sf::Image img = tex->copyToImage();
		mask = createMask(tex, img);
	}
	else
	{
		mask = pair->second;
	}
	return mask;
}

sf::Uint8* CollisionDetection::BitmaskManager::createMask(const sf::Texture* tex, const sf::Image& img)
{
	sf::Uint8* mask = new sf::Uint8[tex->getSize().y * tex->getSize().x];

	for (auto y = 0u; y < tex->getSize().y; y++)
	{
		for (auto x = 0u; x < tex->getSize().x; x++)
		{
			mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
		}
	}

	Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex, mask));
	return mask;
}

CollisionDetection::BitmaskManager bitMaskManager;

bool CollisionDetection::PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit)
{
	sf::FloatRect Intersection;
	if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(),Intersection)) 
	{
		//Might not be needed due to the nature of how our objects move
		sf::IntRect SubRect1 = Object1.getTextureRect();
		sf::IntRect SubRect2 = Object2.getTextureRect();

		auto mask1 = bitMaskManager.getMask(Object1.getTexture());
		auto mask2 = bitMaskManager.getMask(Object2.getTexture());

		for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++)
		{
			for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++)
			{
				sf::Vector2f Obj1_vector = Object1.getInverseTransform().transformPoint(i, j);
				sf::Vector2f Obj2_vector = Object2.getInverseTransform().transformPoint(i, j);

				if (Obj1_vector.x > 0 && Obj1_vector.y > 0 && Obj2_vector.x > 0
					&& Obj2_vector.y > 0 && Obj1_vector.x < SubRect1.width
					&& Obj1_vector.y < SubRect1.height && Obj2_vector.x < SubRect2.width
					&& Obj2_vector.y < SubRect2.height)
				{
					if (bitMaskManager.getPixel(mask1, Object1.getTexture(), (int)(Obj1_vector.x) + SubRect1.left, (int)(Obj1_vector.y) + SubRect1.top) > AlphaLimit &&
						bitMaskManager.getPixel(mask2, Object2.getTexture(), (int)(Obj2_vector.x) + SubRect2.left, (int)(Obj2_vector.y) + SubRect2.top) > AlphaLimit)
					{
						return true;
					}
				}
			}
		}
		//return true;
	}
	return false;
}

//see if i want to add this in later
bool CollisionDetection::BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2)
{
	return false;
}