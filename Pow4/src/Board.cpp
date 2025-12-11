#include "../include/Board.hpp"

#include <iostream>

void Board::initBoard()
{
    for (int cell = 1 ; cell <= ROWS * COLS; ++cell) {
      cells[cell - 1] = ' ';
    }
}

void Board::drawBoard()
{
    std::cout << "\033[0;30m    1       2       3       4       5       6       7    \033[0m\n";
    std::cout << "╔═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╗\n";
    for (int row = 0; row < ROWS; ++row)
    {
        std::cout << "║       ║       ║       ║       ║       ║       ║       ║\n";
        std::cout << "║";
        for (int col = 0; col < COLS; ++col)
        {

            if (cells[row * COLS + col] != 'J' && cells[row * COLS + col] != 'R') {
                std::cout << "   " << ' ' << "   ║";
                continue;
            }
            std::cout << "   ";
            if (cells[row * COLS + col] == 'J') {
                std::cout << "\033[1;33m"
                          << cells[row * COLS + col]
                          << "\033[0m";
            } else {
                std::cout << "\033[1;31m"
                          << cells[row * COLS + col]
                          << "\033[0m";
            } 
            std::cout << "   ║";
        }
        if (row < ROWS - 1) {
            std::cout << "\n╠═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╣\n";
        } else {
            std::cout << "\n╚═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╝\n";
        }
    }
}

bool Board::isMoveValid(int column)
{
    if (column < 1 || column > COLS)
    {
        return false;
    }
    return cells[column - 1] != 'J' && cells[column - 1] != 'R';
}

bool Board::applyMove(int column, char color)
{
    if (!isMoveValid(column)) {
        return false;
    }
    for (int row = ROWS - 1; row >= 0; --row) {
        int index = row * COLS + (column - 1);
        if (cells[index] != 'J' && cells[index] != 'R') {
            cells[index] = color;
            return true;
        }
    }
    return false;
}

bool Board::isBoardFull()
{
    for (const char& cell : cells)
    {
        if (cell != 'J' && cell != 'R')
        {
            return false;
        } 
    }
    return true;
}

bool Board::verifyWin(const int &column, const char &color)
{
    int lastIndex = -1;
    for (int row = 0; row < ROWS; ++row) {
        int index = row * COLS + (column - 1);
        if (cells[index] == color) {
            lastIndex = index;
            break;
        }
    }

    if (lastIndex == -1) {
        return false;
    }

    int directions[8][2] = {
        {0, 1},   // Horizontale droite
        {0, -1},  // Horizontale gauche
        {1, 0},   // Verticale bas
        {-1, 0},  // Verticale haut
        {1, 1},   // Diagonale vers bas droite
        {-1, -1}, // Diagonale vers haut gauche
        {1, -1},  // Diagonale vers bas gauche
        {-1, 1}   // Diagonale vers haut droite
    };

    // TODO 
    // Tip Jules : Faire un array d'array et ne pas faire de tableau C pour itérer dessus
}