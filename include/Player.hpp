#pragma once

#include <string>

struct Player
{
    std::string name;
    char symbol;
    bool isAI = false;
};

Player create_player();

Player create_ai_player(char symbol);
