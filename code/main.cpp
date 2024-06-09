#include"Game.h"
#include<iostream>

int main()
{
    Game game;
    std::srand(static_cast<unsigned>(time(NULL)));

    while (game.getWindowIsOpen())
    {
        game.run();
    }
    
    return 0;
}