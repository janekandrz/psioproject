#pragma once 
#include <SFML/Graphics.hpp>

class GameEntity
{
    public:
        unsigned int m;
        float f,d,t;

        GameEntity();
        GameEntity(unsigned int m, float f, float d, float t);
        ~GameEntity();
};