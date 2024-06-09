#pragma once  
#include"Hero.h"
#include<SFML/Graphics.hpp>

class Target
{
    private:
        sf::Vector2f velocity;
        int targetTextureRand;
        int xvel;
        float tempR;
        sf::Sprite targetSprite;
        sf::Texture targetTextureApple;
        sf::Texture targetTextureOrange;
        sf::Texture targetTexturePear;
        
    public:
        Target();
        Target(float x,float y, int t,float a);
        bool loadTextures();
        void setTexture(int t);
        void setVelocity(float x);
        void movement();
        void rotation(float a);
        bool checkColisonHero(const sf::Vector2i& mousePos);
        sf::Sprite& getTargetSprite();
};

