#include<vector>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

// classes
#include "Scene.h"
#include "Hero.h"
#include "Target.h"

//game engine 
class Game
{
    private:
        //Variables 
        
        //hero
        Hero _hero;

        //window 
        sf::RenderWindow window;
        Scene scene;
        sf::VideoMode videoMode;
    
        //event 
        sf::Event event;

        //restart 
        sf::Sprite restartButtonS;
        sf::Texture restartButtonT;

        //target vector 
        std::vector<Target*> vecTarget;

        //mouse pos 
        sf::Vector2i mousePosWindow;
        sf::Vector2i prevmousePosWindow;

        //font
        sf::Font font;

        //icon
        sf::Image icon;

        //score
        sf::Text scoreText;
        int score;
        sf::Sprite scoreSprite;
        sf::Texture scoreTexture;

        //scoreSummary
        sf::Text scoreScoreSummary;
        sf::Text scoreTextSummary;

        //high score
        sf::Text highScoreText;
        sf::Text highScoreScore;

        //lives 
        sf::Text livesText; 
        int lives;
        sf::Texture livesTexture;
        sf::Sprite livesSprite;

        //velocity
        sf::Vector2f velocity;
        
        sf::SoundBuffer sliceBuffer;
        sf::Sound slice;

        //logic
        float targetSpawnTimer;
        float targetSpawnTimerMax;
        float seconds;
        int maxTargets;
        bool prevHit;
        bool gameOver;
        int highScore;

        //private func 
        void initVariable();
        void initWindow();
        void initIcon();
        void initFont();
        void initScore();
        void initScoreIcon();
        void initLives();
        void initLivesIcon();
        void initRestartButton();
        void initSound();
        void initScoreSummary();
        void initHighScore();
        void initClock();
    public:
        Game();
        virtual ~Game();
        
        //accessor 
        const bool getWindowIsOpen();

        //placeholder

        //func
        void pollEvent();
        int  getLives();
        void drawConsts();
        void drawObjcts();
        bool checkHit();
        void spawnTarget();
        void drawScoreSummary();
        
        //updates 
        void updateMousePos();
        void updateScore();
        void updateHighScore();
        void updateLives();
        void updateTargets();
        void updateClock();

        //printing
        void update();
        void render();
        void restart();
        void run();
};