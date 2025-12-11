#pragma once

#include <string>

struct Player
{
    std::string name;
    char symbol;
    bool isAI = false;
};

/*
    Crée un joueur humain en demandant son nom et un symbole.
    @return Le joueur créé.
*/
Player createPlayer();

/*
    Crée un joueur humain avec un symbole donné.
    @param symbol Le symbole du joueur humain.
    @return Le joueur humain créé.
*/
Player createPlayer(char symbol);

/*
    Crée un joueur IA avec un symbole donné.
    @param symbol Le symbole du joueur IA.
    @return Le joueur IA créé.
*/
Player createAIPlayer(char symbol);