#include"Target.h"
#include <iostream>

Target::Target(){};

Target::Target(float x, float y, int t,float a)
{
    if(!loadTextures())
    {
        std::cerr << "Error loading textures" << std::endl;
    }

    setTexture(t);
    targetSprite.setOrigin
    (
        targetSprite.getOrigin().x+(targetSprite.getLocalBounds().width/2),
        targetSprite.getOrigin().y+(targetSprite.getLocalBounds().height/2)
    );
    targetSprite.setScale(0.5f,0.5f);
    targetSprite.setPosition(x,y);
    setVelocity(x);
};

bool Target::loadTextures()
{
    bool loaded = true;

    if (!targetTextureApple.loadFromFile("bin\\fruit_apple.png"))
    {
        loaded = false;
    }
    if (!targetTextureOrange.loadFromFile("bin\\fruit_orange.png"))
    {
        loaded=false;
    }
    if (!targetTexturePear.loadFromFile("bin\\fruit_pear.png"))
    {
        loaded = false;
    }

    return loaded;
}

void Target::setTexture(int t)
{
    switch (t)
    {
    case 1:
        targetSprite.setTexture(targetTextureApple);
        break;
    case 2:
        targetSprite.setTexture(targetTextureOrange);
        break;
    case 3:
        targetSprite.setTexture(targetTexturePear);
        break;
    }
}

void Target::setVelocity(float x)
{
    if (x >= 500)
    {
        velocity.x = static_cast<float>(rand() % 4 - 4);
    }
    else
    {
        velocity.x = static_cast<float>(rand() % 4 + 1);
    }

    velocity.y = static_cast<float>(-(rand() % 5 + 6));
}

bool Target::checkColisonHero(const sf::Vector2i& mousePos)
{
    return targetSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Target::movement()
{   
    float gravity=0.1;
    velocity.y+=gravity;
    targetSprite.setPosition(targetSprite.getPosition()+velocity);

    this->rotation(1);
}

void Target::rotation(float a)
{   
    float rotation=a;
    targetSprite.rotate(rotation);
}

sf::Sprite& Target::getTargetSprite()
{
    return targetSprite;
}

