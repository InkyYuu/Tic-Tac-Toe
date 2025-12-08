#include "Game.hpp"

#include <iostream>
#include <limits>
#include <string>

void clearScreen()
{
  #ifdef _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
}

static int chooseGameMode() {
  int choice;
  while (true)
  {
    std::cout << "Votre choix : ";
    std::cin >> choice;
    if (!std::cin.fail() && (choice == 1 || choice == 2))
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
    std::cout << "Choix invalide, veuillez entrer 1 ou 2.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void Game::initGame()
{
  board.initBoard();

  clearScreen();
  std::cout << std::endl;
  std::cout << "████████╗██╗ ██████╗████████╗ █████╗  ██████ ████████╗ ██████╗ ███████╗" << std::endl;
  std::cout << "╚══██╔══╝██║██╔════╝╚══██╔══╝██╔══██╗██╔════╝╚══██╔══╝██╔═══██╗██╔════╝" << std::endl;
  std::cout << "   ██║   ██║██║        ██║   ███████║██║        ██║   ██║   ██║█████╗  " << std::endl;
  std::cout << "   ██║   ██║██║        ██║   ██╔══██║██║        ██║   ██║   ██║██╔══╝  " << std::endl;
  std::cout << "   ██║   ██║╚██████╗   ██║   ██║  ██║╚██████╗   ██║   ╚██████╔╝███████╗" << std::endl;
  std::cout << "   ╚═╝   ╚═╝ ╚═════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚══════╝" << std::endl;
  std::cout << std::endl;
  std::cout << "By Kellian Bredeau" << std::endl;
  std::cout << std::endl;

  std::cout << "Choisissez un mode de jeu :\n";
  std::cout << "  1. Deux joueurs\n";
  std::cout << "  2. Un joueur contre l'IA\n\n";

  int modeChoice = chooseGameMode();

  mode = static_cast<GameMode>(modeChoice);

  player1 = createPlayer();
  player2 = (mode == GameMode::VsAI) ? createAIPlayer((player1.symbol == 'X') ? 'O' : 'X') : createPlayer((player1.symbol == 'X') ? 'O' : 'X');

  Board board;
  board.initBoard();

  this->board = board;

  std::string p1 = player1.name + " (" + player1.symbol + ")";
  std::string p2 = player2.name + " (" + player2.symbol + ")";
  std::string text = "  " + p1 + "   VS   " + p2 + "  ";

  std::cout << "\n-----------------------------------------------------------------------\n"<<std::endl;

  board.drawBoard();
} 

void Game::waitForUser()
{
  std::cout << "Appuyez sur Entrée pour continuer...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::runGameLoop()
{
  // Implémentation à venir
}