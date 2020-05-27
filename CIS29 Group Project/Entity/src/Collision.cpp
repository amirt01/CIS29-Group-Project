#include "stdafx.h"
#include "Collision.h"

Collision::Collision(sf::RectangleShape& body):
    body(body){}

Collision::~Collision() {}

bool Collision::checkCollision(Collision& other, float push) {

    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();
    sf::Vector2f thisPosition = getPosition();

    float deltax = otherPosition.x - thisPosition.x;
    float deltay = otherPosition.y - thisPosition.y;

    float intersectx = abs(deltax) - (otherHalfSize.x + thisHalfSize.x);
    float intersecty = abs(deltay) - (otherHalfSize.y + thisHalfSize.y);

   
    if (intersectx < 0.0f && intersecty < 0.0f) {
        return true;
    }

     return false;
}

void Collision::move(float dx, float dy) {
    body.move(dx, dy); 
}

sf::Vector2f Collision::getPosition() { 
    return body.getPosition(); 
}

sf::Vector2f Collision::getHalfSize() { 
    return sf::Vector2f((body.getSize().x) / 2, (body.getSize().y) / 2);
}