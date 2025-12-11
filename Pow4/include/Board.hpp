#pragma once

#include <array>

struct Board
{
    static const int ROWS = 6;
    static const int COLS = 7;
    std::array<char, ROWS * COLS> cells;

    /*
      Initialise le plateau de jeu en remplissant toutes les cellules avec des espaces vides (' ').
    */
    void initBoard();

    /*
      Affiche le plateau de jeu dans la console.
    */
    void drawBoard();

    /*
      Verifie si un coup est valide (c'est-a-dire si la position est dans les limites du plateau et si la cellule est vide).
      @param column La colonne du coup a verifier (1-7).
      @return true si le coup est valide, false sinon.
    */
    bool isMoveValid(int column);

    /*
      Applique un coup sur le plateau de jeu en mettant a jour la cellule correspondante avec la couleur du joueur.
      @param column La colonne du coup a appliquer (1-7).
      @param color La couleur du joueur (ex: 'J' ou 'R').
      @return true si le coup a ete applique avec succes, false sinon.
    */
    bool applyMove(int column, char color);

    /*
      Verifie si le plateau de jeu est plein (c'est-a-dire si toutes les cellules sont remplies).
      @return true si le plateau est plein, false sinon.
    */
    bool isBoardFull();

    /*
      Compte le nombre de jetons consecutifs d'une couleur donnee dans une direction specifique.
      @param color La couleur des jetons a compter.
      @param index L'index de depart dans le tableau des cellules.
      @param deltaRow Le changement de ligne pour la direction (ex: 1 pour bas, -1 pour haut).
      @param deltaCol Le changement de colonne pour la direction (ex: 1 pour droite, -1 pour gauche).
      @return Le nombre de jetons consecutifs trouves dans la direction specifiee.
    */
    int countInDirection(char color, int index, int deltaRow, int deltaCol);

    /*
      Verifie si un joueur a gagne en alignant trois de ses symboles horizontalement, verticalement ou en diagonale.
      @param board Le plateau de jeu actuel.
      @param column La derniere colonne jouee (1-7).
      @return true si le joueur a gagne, false sinon.
    */
    bool verifyWin(const int& column, const char& color);
};