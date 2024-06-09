#pragma once

class Scene
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text scoreText;
    int score;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:

    Scene(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    sf::RenderWindow* getWindow() const;
};