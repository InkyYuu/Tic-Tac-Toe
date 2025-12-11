#include "../include/Game.hpp"

#include <iostream>
#include <windows.h>
#include <limits>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Game game;
    game.initGame();
    game.runGameLoop();
}