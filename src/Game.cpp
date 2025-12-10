#include "Game.hpp"

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
  std::cout << "\033[0m████████╗██╗ ██████╗ ████████╗ █████╗  ██████  ████████╗ ██████╗ ███████╗" << std::endl;
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

  srand(time(NULL));
  this->firstPlayer = rand() % 2;
}

void Game::waitForUser()
{
  std::cout << "Appuyez sur Entrée pour continuer...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Game::askMove(const Player& player) {
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
    if (!std::cin.fail() && position >= 1 && position <= 9 && this->board.isMoveValid(position))
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return position;
    }
    std::cout << "Coup invalide, veuillez entrer un nombre entre 1 et 9.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

int Game::chooseAIMove() {
  for (int pos = 1; pos <= board.SIZE * board.SIZE; ++pos) {
      if (board.isMoveValid(pos) && board.verifyWin(pos, player2.symbol, true))
      {
          return pos;
      }
  }

  for (int pos = 1; pos <= board.SIZE * board.SIZE; ++pos) {
      if (board.isMoveValid(pos) && board.verifyWin(pos, player1.symbol, true))
      {
          return pos;
      }
  }

  bool hasAISymbol = false;
  bool noStrategicMove = true;
  for (int pos = 0; pos < board.SIZE * board.SIZE; ++pos) {
      if (board.cells[pos] == player2.symbol) {
          hasAISymbol = true;
          break;
      }
  }


  if (hasAISymbol) {
    for (int pos = 0; pos < board.SIZE * board.SIZE; ++pos) {
      std::vector<int> strategicPositions;
      if (board.cells[pos] == player2.symbol) {
        int row = pos / board.SIZE;
        int col = pos % board.SIZE;

        // Ligne
        std::vector<int> tempStrategicPositions;
        bool enemyInLine = false;
        for (int c = 0; c < board.SIZE; ++c) {
            int checkPos = row * board.SIZE + c;
            if (board.cells[checkPos] == player1.symbol) {
              enemyInLine = true;
              break;
            }
            if (board.isMoveValid(checkPos + 1) && board.cells[checkPos] != player1.symbol) {
              tempStrategicPositions.push_back(checkPos + 1);
            }
        }
        if (!enemyInLine) {
            strategicPositions.insert(strategicPositions.end(), tempStrategicPositions.begin(), tempStrategicPositions.end());
        }

        // Colonne
        tempStrategicPositions.clear();
        enemyInLine = false;
        for (int r = 0; r < board.SIZE; ++r) {
            int checkPos = r * board.SIZE + col;
            if (board.cells[checkPos] == player1.symbol) {
              enemyInLine = true;
              break;
            }
            if (board.isMoveValid(checkPos + 1) && board.cells[checkPos] != player1.symbol) {
              tempStrategicPositions.push_back(checkPos + 1);
            }
        }
        if (!enemyInLine) {
            strategicPositions.insert(strategicPositions.end(), tempStrategicPositions.begin(), tempStrategicPositions.end());
        }

        // Diagonale principale
        tempStrategicPositions.clear();
        enemyInLine = false;
        if (row == col) {
            for (int i = 0; i < board.SIZE; ++i) {
                int checkPos = i * board.SIZE + i;
                if (board.cells[checkPos] == player1.symbol) {
                  enemyInLine = true;
                  break;
                }
                if (board.isMoveValid(checkPos + 1) && board.cells[checkPos] != player1.symbol) {
                  tempStrategicPositions.push_back(checkPos + 1);
                }
            }
        }
        if (!enemyInLine) {
            strategicPositions.insert(strategicPositions.end(), tempStrategicPositions.begin(), tempStrategicPositions.end());
        }

        // Diagonale secondaire
        tempStrategicPositions.clear();
        enemyInLine = false;
        if (row + col == board.SIZE - 1) {
            for (int i = 0; i < board.SIZE; ++i) {
                int checkPos = i * board.SIZE + (board.SIZE - 1 - i);
                if (board.cells[checkPos] == player1.symbol) {
                  break;
                }
                if (board.isMoveValid(checkPos + 1) && board.cells[checkPos] != player1.symbol) {
                    tempStrategicPositions.push_back(checkPos + 1);
                }
            }
        }
        if (!enemyInLine) {
            strategicPositions.insert(strategicPositions.end(), tempStrategicPositions.begin(), tempStrategicPositions.end());
        }
      }
      
      if (!strategicPositions.empty()) {
        srand(time(NULL));
        return strategicPositions[rand() % strategicPositions.size()];
      }
    }

    noStrategicMove = true;
  }

  if (!hasAISymbol || noStrategicMove) {
    const int preferredMoves[] = {5, 1, 3, 7, 9, 2, 4, 6, 8};
    for (int pos : preferredMoves) {
      if (board.isMoveValid(pos)) {
          return pos;
      }
    }
  }

  return -1;
}

void Game::runGameLoop() {
  std::cout << "Le joueur qui commence est : \033[1;32m" 
            << ((firstPlayer == 1) ? player1.name : player2.name) 
            << "\033[0m!\n";

  waitForUser();

  bool IA = (mode == GameMode::VsAI);
  clearScreen();

  while (true) {
      board.drawBoard();
      Player currentPlayer = (firstPlayer == 1) ? player1 : player2;

      int move;
      if (IA && currentPlayer.isAI) {
          move = chooseAIMove();
          if (move == -1) {
              std::cout << "L'IA n'a pas pu trouver de coup valide.\n";
              break;
          }
      } else {
          move = askMove(currentPlayer);
      }
      
      board.applyMove(move, currentPlayer.symbol);
      clearScreen();

      if (board.verifyWin(move, currentPlayer.symbol, false)) {
        board.drawBoard();
        if (IA && currentPlayer.isAI) {
            std::cout << "\033[1;31mL'IA a gagné! Mieux vaut réessayer.\033[0m\n";
            break;
        }
        std::cout << "\033[1;32mFélicitations " << currentPlayer.name << "! Vous avez gagné!\033[0m\n";
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