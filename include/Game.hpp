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
    int firstPlayer;

    void initGame();

    void runGameLoop();

    void waitForUser();

    int askMove(const Player& player);

    int chooseAIMove();
};

void clearScreen();



