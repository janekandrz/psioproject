#include"Hero.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>

Hero::Hero():GameEntity(), maxPoints(0), fadeSpeed(0), maxDiff(0), maxThick(0) {}

Hero::Hero(unsigned int maxPoints, float fadeSpeed, float maxDiff, float maxThicc):
    maxPoints(maxPoints), 
    fadeSpeed(fadeSpeed), 
    maxDiff(maxDiff), 
    maxThick(maxThicc){}

void Hero::trailUpdate(const sf::Vector2f& newPosition)
{
    if (!points.empty()) 
    {
        std::vector<sf::Vector2f> interpolatedPoints = interpolate(points.front(), newPosition, maxDiff);
        for (const auto& point : interpolatedPoints) 
        {
            points.push_front(point);
        }
    } 
    else 
    {
        points.push_front(newPosition);
    }

    while (points.size() > maxPoints) 
    {
        points.pop_back();
    }
}

void Hero::trailDraw(sf::RenderWindow& window) 
{
    sf::VertexArray trail(sf::TrianglesStrip);
        float thickness = maxThick;
        float thicknessDecrement = maxThick / maxPoints;
        float opacity = 255.0f;
        float opacityDecrement = 255.0f / maxPoints;

        for (size_t i = 0; i < points.size(); ++i) 
        {
            sf::Vector2f direction;
            if (i + 1 < points.size()) 
            {
                direction = points[i] - points[i + 1];
            } 
            else if (i > 0) 
            {
                direction = points[i - 1] - points[i];
            }

            direction = normalize(direction);
            sf::Vector2f perpendicular(-direction.y, direction.x);

            sf::Color color(255, 255, 255, static_cast<sf::Uint8>(opacity));
            trail.append(sf::Vertex(points[i] + perpendicular * thickness, color));
            trail.append(sf::Vertex(points[i] - perpendicular * thickness, color));

            thickness -= thicknessDecrement;
            opacity -= opacityDecrement;
        }

    window.draw(trail);
}

sf::Vector2f Hero::normalize(const sf::Vector2f& vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        if (length != 0) 
        {
            return vector / length;
        }
    return vector;
}

std::vector<sf::Vector2f> Hero::interpolate(const sf::Vector2f& start, const sf::Vector2f& end, float maxDistance) 
{
    std::vector<sf::Vector2f> points;
    sf::Vector2f direction = end - start;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > maxDistance) 
    {
        int numPoints = static_cast<int>(distance / maxDistance);
        sf::Vector2f step = direction / static_cast<float>(numPoints);
        for (int i = 1; i <= numPoints; ++i) 
        {
            points.push_back(start + step * static_cast<float>(i));
        }
    }

    points.push_back(end);
    return points;
}

