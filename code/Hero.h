#pragma once 
#include "GameEntity.h"
#include<SFML/Graphics.hpp>
#include <deque>

class Hero:public GameEntity
{
    private:
        std::deque<sf::Vector2f>points;
        unsigned int maxPoints;
        float fadeSpeed;
        float maxDiff;
        float maxThick;

    public:
        Hero();
        Hero(unsigned int maxPoints, float fadeSpeed, float maxDiff, float maxThick);

        void trailUpdate(const sf::Vector2f& newPosition);
        void trailDraw(sf::RenderWindow& window);
        sf::Vector2f normalize(const sf::Vector2f& vector);
        std::vector<sf::Vector2f> interpolate(const sf::Vector2f& start, const sf::Vector2f& end, float maxDistance);
};