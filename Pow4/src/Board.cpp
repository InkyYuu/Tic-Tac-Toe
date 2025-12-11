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

int Board::countInDirection(char color, int index, int deltaRow, int deltaCol)
{
    int count = 1;
    int row = index / COLS;
    int col = index % COLS;

    while (true) {
        row += deltaRow;
        col += deltaCol;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            break;
        }

        int newIndex = row * COLS + col;
        if (cells[newIndex] == color) {
            count++;
        } else {
            break;
        }
    }

    row = index / COLS;
    col = index % COLS;

    while (true) {
        row -= deltaRow;
        col -= deltaCol;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            break;
        }

        int newIndex = row * COLS + col;
        if (cells[newIndex] == color) {
            count++;
        } else {
            break;
        }
    }

    return count;
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

    std::array<std::array<int, 2>, 4> dirArray = {{
        {0, 1},   // Horizontale
        {1, 0},   // Verticale
        {1, 1},   // Diagonale vers bas droite
        {1, -1},  // Diagonale vers bas gauche
    }};

    for (std::array<int, 2> dir : dirArray) {
        int count = countInDirection(color, lastIndex, dir[0], dir[1]);
        if (count >= 4) {
            return true;
        }
    }
    return false;
}