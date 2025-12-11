#include "../include/Game.hpp"

#include <iostream>
#include <windows.h>
#include <limits>

static bool createYesNoPrompt(const std::string& prompt) {
    char choice;
    while (true) {
        std::cout << prompt << " (o/n) : ";
        std::cin >> choice;
        if (choice == 'o' || choice == 'O') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else {
            std::cout << "Choix invalide, veuillez entrer 'o' pour oui ou 'n' pour non.\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Game game;
    game.initGame();
    game.runGameLoop();

    bool playAgain = createYesNoPrompt("Voulez-vous jouer à nouveau ?");

    while (playAgain) {
        game.initGame();
        game.runGameLoop();

        playAgain = createYesNoPrompt("Voulez-vous jouer à nouveau ?");
    }

    return 0;
}