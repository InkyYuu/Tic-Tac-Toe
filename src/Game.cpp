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
  std::cout << "████████╗██╗ ██████╗ ████████╗ █████╗  ██████  ████████╗ ██████╗ ███████╗" << std::endl;
  std::cout << "╚══██╔══╝██║██╔════╝ ╚══██╔══╝██╔══██╗██╔════╝ ╚══██╔══╝██╔═══██╗██╔════╝" << std::endl;
  std::cout << "   ██║   ██║██║         ██║   ███████║██║         ██║   ██║   ██║█████╗  " << std::endl;
  std::cout << "   ██║   ██║██║         ██║   ██╔══██║██║         ██║   ██║   ██║██╔══╝  " << std::endl;
  std::cout << "   ██║   ██║╚██████╗    ██║   ██║  ██║╚██████╗    ██║   ╚██████╔╝███████╗" << std::endl;
  std::cout << "   ╚═╝   ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝ ╚══════╝" << std::endl;
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

  this->firstPlayer = rand() % 2 + 1;
} 

void Game::waitForUser()
{
  std::cout << "Appuyez sur Entrée pour continuer...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int askMove(const Player& player, Board& board) {
  int position;
  while (true)
  {
    if (player.symbol == 'X') {
        std::cout << "\033[1;34m";
    } else {
        std::cout << "\033[1;31m";
    } 
    std::cout << player.name << " (" << player.symbol << "), entrez votre coup (1-9) : ";
    std::cin >> position;
    if (!std::cin.fail() && position >= 1 && position <= 9 && board.isMoveValid(position))
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return position;
    }
    std::cout << "Coup invalide, veuillez entrer un nombre entre 1 et 9.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

static int chooseAIMove(Board& board) {
  // Doit choisir un coup intelligent
  // Soit il gagne directement s'il peut
  // Soit il bloque le joueur s'il va gagner au prochain tour
  // Sinon, il choisit une position intéressante pour lui (en fonction de ses anciens coups)
}

void Game::runGameLoop()
{
  
}