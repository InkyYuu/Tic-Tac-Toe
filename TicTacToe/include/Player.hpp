#pragma once

#include <string>

struct Player
{
    std::string name;
    char symbol;
    bool isAI = false;
};

Player createPlayer();

Player createPlayer(char symbol);

Player createAIPlayer(char symbol);