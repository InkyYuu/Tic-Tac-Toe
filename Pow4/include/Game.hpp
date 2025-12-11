#pragma once

#include "../include/Board.hpp"
#include "../include/Player.hpp"

struct Game
{
    Board board;
    Player player1;
    Player player2;
    int firstPlayer;

    void initGame();

    void runGameLoop();

    void waitForUser();

    int askMove(const Player& player);
};

void clearScreen();



