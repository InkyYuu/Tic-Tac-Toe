#pragma once

#include <array>

struct Board
{
    static const int SIZE = 3;
    std::array<char, SIZE * SIZE> cells;

    /*
      Initialise le plateau de jeu en remplissant toutes les cellules avec des espaces vides. (' ')
      @param board Le plateau de jeu a initialiser.
    */
    void initBoard();

    /*
      Affiche le plateau de jeu dans la console.
      @param board Le plateau de jeu a afficher.
    */
    void drawBoard();

    /*
      Verifie si un coup est valide (c'est-a-dire si la position est dans les limites du plateau et si la cellule est vide).
      @param board Le plateau de jeu actuel.
      @param position La position du coup a verifier (1-9).
      @return true si le coup est valide, false sinon.
    */
    bool isMoveValid(int position);

    /*
      Applique un coup sur le plateau de jeu en mettant a jour la cellule correspondante avec le symbole du joueur.
      @param board Le plateau de jeu a mettre a jour.
      @param position La position du coup a appliquer (1-9).
      @param symbol Le symbole du joueur (ex: 'X' ou 'O').
    */
    bool applyMove(int position, char symbol);

    /*
      Verifie si le plateau de jeu est plein (c'est-a-dire si toutes les cellules sont remplies).
      @param board Le plateau de jeu a verifier.
      @return true si le plateau est plein, false sinon.
    */
    bool isBoardFull();

    /*
      Verifie si un joueur a gagne en alignant trois de ses symboles horizontalement, verticalement ou en diagonale.
      @param board Le plateau de jeu actuel.
      @param position La derniere position jouee (1-9).
      @return true si le joueur a gagne, false sinon.
    */
    bool verifyWin(int position);
};