#include "../include/Game.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

void clearScreen()
{
  #ifdef _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
}

void Game::waitForUser()
{
  std::cout << "Appuyez sur Entrée pour continuer...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::initGame()
{
  board.initBoard();

  clearScreen();
  std::cout << std::endl;
  std::cout << "\033[0m██████╗  ██████╗ ██╗    ██╗ ╗ \n";
  std::cout << "██╔══██╗██╔═══██╗██║    ██║    ██  ██╔\n";
  std::cout << "██████╔╝██║   ██║██║ █╗ ██║    ██╔╝██║ \n";
  std::cout << "██╔═══╝ ██║   ██║██║███╗██║     █████║\n";
  std::cout << "██║     ╚██████╔╝╚███╔███╔╝        ██║\n";
  std::cout << "╚═╝      ╚═════╝  ╚══╝╚══╝         ╚═╝\n";
  std::cout << std::endl;
  std::cout << "By Kellian Bredeau" << std::endl;
  std::cout << std::endl;

  waitForUser();
  clearScreen();

  Board board;
  board.initBoard();

  player1 = createPlayer();
  player2 = createPlayer((player1.color == 'J') ? 'R' : 'J');

  std::string p1 = player1.name + " (" + player1.color + ")";
  std::string p2 = player2.name + " (" + player2.color + ")";
  std::string text = "  " + p1 + "   VS   " + p2 + "  ";
  std::cout << text << std::endl;

  srand(time(NULL));
  this->firstPlayer = rand() % 2;
}

int Game::askMove(const Player& player) {
  int column;
  while (true)
  {
    if (player.color == 'J') {
        std::cout << "\033[1;33m";
    } else {
        std::cout << "\033[1;31m";
    }
    std::cout << player.name << ", entrez le numéro de la colonne (1-7) où vous souhaitez jouer : ";
    std::cin >> column;
    if (!std::cin.fail() && board.isMoveValid(column))
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return column;
    } else {
        std::cout << "Coup invalide, recommencez.\n";
    }
    std::cout << "\033[0m";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void Game::runGameLoop() {
  std::cout << "Le joueur qui commence est : \033[1;32m" 
            << ((firstPlayer == 1) ? player1.name : player2.name) 
            << "\033[0m!\n";

  waitForUser();

  clearScreen();

  while (true) {
      board.drawBoard();
      Player currentPlayer = (firstPlayer == 1) ? player1 : player2;

      int move = askMove(currentPlayer);
      
      board.applyMove(move, currentPlayer.color);
      clearScreen();

      if (board.verifyWin(move, currentPlayer.color)) {
        board.drawBoard();
        std::cout << "\033[1;32mFélicitations " << currentPlayer.name << "! Vous avez gagné la partie!\033[0m\n";
        break;
      }

      if (board.isBoardFull()) {
        board.drawBoard();
        std::cout << "\033[1;33mMatch nul! Le plateau est plein.\033[0m\n";
        break;
      }

      firstPlayer = (firstPlayer == 1) ? 2 : 1;
  }
}