#pragma once

#include <string>

struct Player
{
    std::string name;
    char color;
};

Player createPlayer();

Player createPlayer(char color);