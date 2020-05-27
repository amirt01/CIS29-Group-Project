#include "stdafx.h"
#include "Collision.h"

Collision::Collision(sf::RectangleShape& body):
    body(body){}

Collision::~Collision() {}

bool Collision::checkCollision(Collision& other, float push) {
    {
        sf::Vector2f otherPosition = other.getPosition();
        sf::Vector2f otherHalfSize = other.getHalfSize();
        sf::Vector2f thisPosition = getPosition();
        sf::Vector2f thisHalfSize = getHalfSize();

        float deltax = otherPosition.x - thisPosition.x;
        float deltay = otherPosition.y - thisPosition.y;

        float intersectx = abs(deltax) - (otherHalfSize.x + thisHalfSize.x);
        float intersecty = abs(deltay) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectx < 0.0f && intersecty < 0.0f) {

            /**if we want the object and player to "push/bounce" off each other when they collide
            direction it "pushes" off each other depends if there more overlap in the x or y direction
            push = std::min(std::max(push, 0.0f), 1.0f); //clamping
            if (abs(intersectx) < abs(intersecty)) {
                if (deltax > 0.0f) {
                    move(intersectx * (1.0f - push), 0.0f);
                    other.move(-intersectx*push, 0.0f);
                }
                else {
                    move(-intersectx * (1.0f - push), 0.0f);
                    other.move(intersectx * push, 0.0f);
                }
            }
            else {
                if (deltay > 0.0f) {
                    move(0.0f, intersecty * (1.0f - push));
                    other.move(0.0f, -intersecty * push);
                }
                else {
                    move(0.0f, -intersecty * (1.0f - push));
                    other.move(0.0f, intersecty * push);
                }
            }**/
            return true;
        }

        return false;
    }
}

void Collision::move(float dx, float dy) {
    body.move(dx, dy); 
}

sf::Vector2f Collision::getPosition() { 
    return body.getPosition(); 
}

sf::Vector2f Collision::getHalfSize() { 
    return body.getSize(); 
}