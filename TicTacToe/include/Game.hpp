#pragma once

#include "../include/Board.hpp"
#include "../include/Player.hpp"

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

    /*
        Initialise le jeu en configurant les joueurs et le mode de jeu. 
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

    /*
        Choisit le mouvement de l'IA. Fais un coup gagnant si possible, bloque un coup gagnant de l'adversaire sinon, ou choisit une position intéressante afin de continuer une ligne. Si aucune de ces options n'est possible, choisit une position aléatoire.
        @return La position choisie par l'IA.
    */
    int chooseAIMove();
};

/*
    Efface l'écran de la console.
*/
void clearScreen();



