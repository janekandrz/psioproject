#include "Game.h"

#include<cmath>
#include<iostream>

Game::Game()
    :scene(window),
    _hero(100,15.0f,2.0f,10.0f),
    window(sf::VideoMode(1024,576),"Fruit Ninja Project", sf::Style::Titlebar | sf::Style::Close)
{
    this->initVariable();
    this->initWindow();
}

Game::~Game(){}

//ptivate func 
void Game::initVariable()
{
    //logic innit
    this->score=0;
    this->lives=3;
    this->gameOver=false;
    this->targetSpawnTimer=0.f;
    this->targetSpawnTimerMax=200.f;
    this->maxTargets=1000;
    this->prevHit=false;
}

void Game::initWindow()
{
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    this->initFont();
    this->initIcon();
    this->initRestartButton();
    this->initScore();
    this->initScoreIcon();
    this->initLives();
    this->initLivesIcon();
    this->initScoreSummary();
    this->initHighScore();
}

void Game::initFont()
{
    if (!font.loadFromFile("bin\\Anton-Regular.ttf")) 
    {
        std::cerr << "Error loading font" << std::endl;
    }
}

void Game::initScore()
{
    this->scoreText.setFont(font);
    this->scoreText.setCharacterSize(36);
    this->scoreText.setFillColor(sf::Color(186, 102, 19, 255));
    this->scoreText.setPosition(60.f, 10.f);
    this->scoreText.setString("000");
}

void Game::initScoreIcon()
{
    if(!scoreTexture.loadFromFile("bin\\fruit_banana.png"))
    {
        std::cerr << "Error loading score icon" << std::endl;
    }

    this->scoreSprite.setTexture(scoreTexture);
    this->scoreSprite.setScale(0.15f,0.15f);
    this->scoreSprite.setPosition(10.f,10.f);
}

void Game::initLives()
{
    this->livesText.setFont(font);
    this->livesText.setCharacterSize(36);
    this->livesText.setFillColor(sf::Color::Red);
    this->livesText.setPosition(window.getSize().x - 30.f, 10.f);
    this->livesText.setString(std::to_string(lives));
}

void Game::initLivesIcon()
{
    if(!livesTexture.loadFromFile("bin\\heart.png"))
    {
        std::cerr << "Error loading lives icon" << std::endl;
    }

    this->livesSprite.setTexture(livesTexture);
    this->livesSprite.setScale(1.f,1.f);
    this->livesSprite.setPosition(window.getSize().x-80.f,5.f);
}

void Game::initIcon()
{
    if (!icon.loadFromFile("bin\\melonslice.jpg"))
    {
        std::cerr << "Error loading icon" << std::endl;
    }

    window.setIcon(icon.getSize().x , icon.getSize().y , icon.getPixelsPtr());
}

void Game::initRestartButton()
{
    if (!restartButtonT.loadFromFile("bin\\restart_button.png"))
    {
        std::cerr << "Error loading restart button texture" << std::endl;
    }

    this->restartButtonS.setTexture(restartButtonT);
    this->restartButtonS.setPosition(
        static_cast<float>((window.getSize().x)/2-(restartButtonS.getGlobalBounds().width)/2), 
        static_cast<float>((window.getSize().y)/2-(restartButtonS.getGlobalBounds().height)/2)
        );
}

void Game::initSound()
{
    if (!sliceBuffer.loadFromFile("bin\\swordsound.wav"))
    {
        std::cout << "Failed to load sound from file" << std::endl;
    }

    slice.setBuffer(sliceBuffer);
}

void Game::initScoreSummary()
{
    this->scoreScoreSummary.setFont(font);
    this->scoreScoreSummary.setCharacterSize(50);
    this->scoreScoreSummary.setFillColor(sf::Color(186, 102, 19, 255));
    this->scoreScoreSummary.setString("0");
    this->scoreScoreSummary.setPosition(475.f,200.f);

    this->scoreTextSummary.setFont(font);
    this->scoreTextSummary.setCharacterSize(50);
    this->scoreTextSummary.setFillColor(sf::Color(186, 102, 19, 255));
    this->scoreTextSummary.setString("Your Score");
    this->scoreTextSummary.setPosition(405.f,150.f);
}

void Game::initHighScore()
{
    this->highScoreText.setFont(font);
    this->highScoreText.setCharacterSize(36);
    this->highScoreText.setFillColor(sf::Color(186, 102, 19, 255));
    this->highScoreText.setString("High Score");
    this->highScoreText.setPosition(window.getSize().x-160,window.getSize().y-40);

    this->highScoreScore.setFont(font);
    this->highScoreScore.setCharacterSize(36);
    this->highScoreScore.setFillColor(sf::Color(186, 102, 19, 255));
    this->highScoreScore.setPosition(window.getSize().x-60,window.getSize().y-80);
}

//func
void Game::pollEvent()
{
    //Event polling 
    while (window.pollEvent(this->event))
    {
        switch(this->event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if(gameOver && this->event.mouseButton.button == sf::Mouse::Left)
                {
                    if(restartButtonS.getGlobalBounds().contains(this->mousePosWindow.x,this->mousePosWindow.y))
                    {
                        this->restart();
                    }
                }
                break;
        }
    }
} 

void Game::updateMousePos()
{
    this->prevmousePosWindow=this->mousePosWindow;
    this->mousePosWindow=sf::Mouse::getPosition(this->window);
}

bool Game::checkHit()
{
    for(Target* target : vecTarget)
    {
        if(target->checkColisonHero(mousePosWindow))
        {
            return true;
        }
    }
    return false;
}

void Game::updateScore()
{
    bool hit= this->checkHit();

    if (hit && !this->prevHit)
    {
        this->score=this->score+1;
        
        if(this->score<10)
        {
            scoreText.setString("00" + std::to_string(score));
        }
        if(this->score>=10)
        {
            scoreText.setString("0" + std::to_string(score));
        }
        if(this->score>=100)
        {
            scoreText.setString(std::to_string(score));
        }
    }

    this->prevHit = hit;
}

void Game::updateHighScore()
{
    if(score>highScore)
    {
        this->highScore=this->score;

        if(this->highScore<10)
        {
            highScoreScore.setString("00" + std::to_string(highScore));
        }
        if(this->highScore>=10)
        {
            highScoreScore.setString("0" + std::to_string(highScore));
        }
        if(this->highScore>=100)
        {
            highScoreScore.setString(std::to_string(highScore));
        }
    }
}

void Game::updateLives()
{
    for (auto it = this->vecTarget.begin(); it != this->vecTarget.end();)
    {
        if ((*it)->getTargetSprite().getPosition().y > window.getSize().y)
        {
            this->lives--;
            this->livesText.setString(std::to_string(lives));
            it = this->vecTarget.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::updateTargets()
{
    if(this->vecTarget.size() < this->maxTargets)
    {
        if(this->targetSpawnTimer >= this-> targetSpawnTimerMax)
        {
            this->targetSpawnTimer=0;
            this->spawnTarget();
            int minTime=50;
            int maxTime=250;
            this->targetSpawnTimer=minTime + rand() % (maxTime-minTime+1);
        }
        else
        {
            this-> targetSpawnTimer += 1.f; 
        }
    }

    for(Target* target :vecTarget)
    {   
        target->movement();
        
        if(target->checkColisonHero(mousePosWindow))
        {
            slice.play();
            vecTarget.erase(std::remove_if(vecTarget.begin(),vecTarget.end(),
            [this](Target* target) { return target->checkColisonHero(mousePosWindow);}),
            vecTarget.end());
        }
    }
}   

void Game::spawnTarget()
{
    float x=static_cast<float>(rand() % static_cast<int>(window.getSize().x - 20));
    float y= static_cast<float>(window.getSize().y-1);

        vecTarget.emplace_back(new Target
            (
                x,
                y,
                rand()%3 + 1,
                rand()%9 - 4
            )
        );
} 

void Game::drawScoreSummary()
{
    window.draw(this->scoreTextSummary);
    
        if(this->score<10){
            scoreScoreSummary.setString("00" + std::to_string(score));
        }
        if(this->score>=10){
            scoreScoreSummary.setString("0" + std::to_string(score));
        }
        if(this->score>=100){
            scoreScoreSummary.setString(std::to_string(score));
        }

    window.draw(this->scoreScoreSummary);
}

void Game::drawConsts()
{
    window.draw(this->scoreSprite);
    window.draw(this->scoreText);
    window.draw(this->livesSprite);
    window.draw(this->livesText);
    window.draw(this->highScoreText);
    window.draw(this->highScoreScore);
}

void Game::drawObjcts() 
{
    if(!gameOver)
    {
        scene.draw(window);

        for(Target* target: vecTarget)
        {
            window.draw(target->getTargetSprite());
        }

        this->drawConsts();

        

        //hero always last 
        _hero.trailDraw(window);
    }      
    else
    {
        scene.draw(window);

        window.draw(this->restartButtonS);

        this->livesText.setString("0");
        this->drawConsts();

        this->drawScoreSummary();
        _hero.trailDraw(window);
    }
}
//dont touch always last 

//accesor 
const bool Game::getWindowIsOpen()
{
    return window.isOpen();
}

int Game::getLives()
{
    return lives;
}

void Game::update()
{
    this->pollEvent();
    window.pollEvent(this->event);
    this->updateMousePos();
    _hero.trailUpdate(static_cast<sf::Vector2f>(mousePosWindow));
    this->updateLives();
    if(!gameOver)
    {
        this->updateHighScore();
        this->updateScore();
        this->updateTargets();
    }
    if(lives==0)
    {
        gameOver=true;
    }
}

void Game::render()
{
    window.clear();

    this->drawObjcts();

    window.display();
}

void Game::restart()
{
    this->initVariable();
    this->initWindow();
    this->initLives();
    this->vecTarget.clear();
}

void Game::run()
{
    this->update(); 
    this->render();
}