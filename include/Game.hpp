#pragma once

#include "Board.hpp"
#include "Player.hpp"

enum class GameMode
{
    TwoPlayers = 1,
    VsAI = 2
};

struct Game
{
    Board board;
    Player player1;
    Player player2;
    GameMode mode;

    void initGame();

    void runGameLoop();

    void waitForUser();
};

void clearScreen();



