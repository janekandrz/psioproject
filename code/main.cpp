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
    //End of app 
    return 0;
}