
#include<iostream>
#include<SFML/Graphics.hpp>
#include"Scene.h"

Scene::Scene(sf::RenderWindow& window)
    :window(window)
{
    if(!backgroundTexture.loadFromFile("C:/vscode/psioproject/bin/background.png"))
    {
        std::cerr << "Error loading backgroundTexture" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect spriteSize = backgroundSprite.getLocalBounds();

    float scaleX = static_cast<float>(windowSize.x) / spriteSize.width;
    float scaleY = static_cast<float>(windowSize.y) / spriteSize.height;

    backgroundSprite.setScale(scaleX, scaleY);
}

void Scene::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
}


