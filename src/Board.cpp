#include "../include/Board.hpp"

#include <iostream>

void Board::initBoard()
{
    for (int cell = 1 ; cell <= SIZE * SIZE; ++cell) {
      cells[cell - 1] = static_cast<char>('0' + cell);
    }
}

static void print_separator()
{
    std::cout << "+---+---+---+\n";
}

void Board::drawBoard()
{
    print_separator();
    for (int row = 0; row < SIZE; ++row)
    {
        std::cout << "|";
        for (int col = 0; col < SIZE; ++col)
        {
            std::cout << " " << cells[row * SIZE + col] << " |";
        }
        std::cout << "\n";
        print_separator();
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

bool Board::verifyWin(int position)
{
    char symbol = cells[position - 1];
    int row = (position - 1) / SIZE;
    int col = (position - 1) % SIZE;
    bool win;
    
    win = true;
    for (int c = 0; c < SIZE; ++c)
    {
        if (cells[row * SIZE + c] != symbol)
        {
            win = false;
            break;
        }
    }
    if (win) return true;

    win = true;
    for (int r = 0; r < SIZE; ++r)
    {
        if (cells[r * SIZE + col] != symbol)
        {
            win = false;
            break;
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
                win = false;
                break;
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
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    return false;
}