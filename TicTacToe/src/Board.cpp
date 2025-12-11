#include "../include/Board.hpp"

#include <iostream>

void Board::initBoard()
{
    for (int cell = 1 ; cell <= SIZE * SIZE; ++cell) {
      cells[cell - 1] = static_cast<char>('0' + cell);
    }
}

void Board::drawBoard()
{
    std::cout << "\033[0m╔═════════╦═════════╦═════════╗\n";
    for (int row = 0; row < SIZE; ++row)
    {
        std::cout << "║";
        for (int col = 0; col < SIZE; ++col)
        {
            if (cells[row * SIZE + col] != 'X' && cells[row * SIZE + col] != 'O') {
                std::cout << " " << "\033[0;30m" << cells[row * SIZE + col] << "\033[0m" << "       ║";
                continue;
            }
            else{
                std::cout << " " << "\033[0;30m \033[0m" << "       ║";
            }

        }
        std::cout << "\n║";
        for (int col = 0; col < SIZE; ++col)
        {
            if (cells[row * SIZE + col] != 'X' && cells[row * SIZE + col] != 'O') {
                std::cout << "    " << ' ' << "    ║";
                continue;
            }
            std::cout << "    ";
            if (cells[row * SIZE + col] == 'X') {
                std::cout << "\033[1;34m"
                          << cells[row * SIZE + col]
                          << "\033[0m";
            } else {
                std::cout << "\033[1;31m"
                          << cells[row * SIZE + col]
                          << "\033[0m";
            } 
            std::cout << "    ║";
        }
        std::cout << "\n║         ║         ║         ║\n";
        if (row < SIZE - 1) {
            std::cout << "╠═════════╬═════════╬═════════╣\n";
        } else {
            std::cout << "╚═════════╩═════════╩═════════╝\033[0m\n";
        }
        
    }
}

bool Board::isMoveValid(int position)
{
    if (position < 1 || position > SIZE * SIZE)
    {
        return false;
    }
    return cells[position - 1] != 'X' && cells[position - 1] != 'O';
}

bool Board::applyMove(int position, char symbol)
{
    if (!isMoveValid(position)) {
        return false;
    }
    cells[position - 1] = symbol;
    return true;
}

bool Board::isBoardFull()
{
    for (char cell : cells)
    {
        if (cell != 'X' && cell != 'O')
        {
            return false;
        }
    }
    return true;
}

bool Board::verifyWin(const int &position, const char &symbol, bool predictive)
{
    int row = (position - 1) / SIZE;
    int col = (position - 1) % SIZE;
    bool win;
    
    win = true;
    for (int c = 0; c < SIZE; ++c)
    {
        if (cells[row * SIZE + c] != symbol)
        {
            if (predictive && row * SIZE + c + 1 == position) {
                continue;
            } else {
                win = false;
                break;
            }
        }
    }
    if (win) return true;

    win = true;
    for (int r = 0; r < SIZE; ++r)
    {
        if (cells[r * SIZE + col] != symbol)
        {
            if (predictive && r * SIZE + col + 1 == position) {
                continue;
            } else {
                win = false;
                break;
            }
        }
    }
    if (win) return true;

    if (row == col)
    {
        win = true;
        for (int i = 0; i < SIZE; ++i)
        {
            if (cells[i * SIZE + i] != symbol)
            {
                if (predictive && i * SIZE + i + 1 == position) {
                    continue;
                } else {
                    win = false;
                    break;
                }
            }
        }
        if (win) return true;
    }

    if (row + col == SIZE - 1)
    {
        win = true;
        for (int i = 0; i < SIZE; ++i)
        {
            if (cells[i * SIZE + (SIZE - 1 - i)] != symbol)
            {
                if (predictive && i * SIZE + (SIZE - 1 - i) + 1 == position) {
                    continue;
                } else {
                    win = false;
                    break;
                }
            }
        }
        if (win) return true;
    }

    return false;
}