#pragma once

#include <array>

struct Board
{
    static const int SIZE = 3;
    std::array<char, SIZE * SIZE> cells;

    /*
      Initialise le plateau de jeu en remplissant toutes les cellules avec le numéro de la position. ('1' à '9')
    */
    void initBoard();

    /*
      Affiche le plateau de jeu dans la console.
    */
    void drawBoard();

    /*
      Verifie si un coup est valide (c'est-a-dire si la position est dans les limites du plateau et si la cellule est vide).
      @param position La position du coup a verifier (1-9).
      @return true si le coup est valide, false sinon.
    */
    bool isMoveValid(int position);

    /*
      Applique un coup sur le plateau de jeu en mettant a jour la cellule correspondante avec le symbole du joueur.
      @param position La position du coup a appliquer (1-9).
      @param symbol Le symbole du joueur (ex: 'X' ou 'O').
      @return true si le coup a ete applique avec succes, false sinon.
    */
    bool applyMove(int position, char symbol);

    /*
      Verifie si le plateau de jeu est plein (c'est-a-dire si toutes les cellules sont remplies).
      @return true si le plateau est plein, false sinon.
    */
    bool isBoardFull();

    /*
      Verifie si un joueur a gagne en alignant trois de ses symboles horizontalement, verticalement ou en diagonale.
      @param position La derniere position jouee (1-9).
      @param symbol Le symbole du joueur.
      @param predictive Indique si la verification est faite a titre predictif (le coup n'a pas encore ete applique).
      @return true si le joueur a gagne, false sinon.
    */
    bool verifyWin(const int& position, const char& symbol, bool predictive);
};