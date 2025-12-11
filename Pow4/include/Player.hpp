#pragma once

#include <string>

struct Player
{
    std::string name;
    char color;
};

/*
    Crée un joueur humain en demandant son nom et une couleur.
    @return Le joueur créé.
*/
Player createPlayer();

/*
    Crée un joueur humain avec une couleur donnée.
    @param color La couleur du joueur humain.
    @return Le joueur humain créé.
*/
Player createPlayer(char color);