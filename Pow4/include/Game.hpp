#pragma once

#include "../include/Board.hpp"
#include "../include/Player.hpp"

struct Game
{
    Board board;
    Player player1;
    Player player2;
    int firstPlayer;

    /*
        Initialise le jeu en configurant les joueurs et les couleurs. 
    */
    void initGame();

    /*
        Lance la boucle principale du jeu.
    */
    void runGameLoop();

    /*
        Attend l'entrée de l'utilisateur (bouton Entrée).
    */
    void waitForUser();

    /*
        Demande à un joueur de faire un mouvement et vérifie sa validité.
        @param player Le joueur qui doit faire un mouvement.
        @return La position choisie par le joueur.
    */
    int askMove(const Player& player);
};

void clearScreen();



