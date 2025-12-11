#include "../include/Player.hpp"

#include <iostream>
#include <limits>

static std::string askName()
{
    std::string name;
    std::cout << "Entrez le nom du joueur : ";
    std::getline(std::cin >> std::ws, name);
    return name;
}

static char askSymbol()
{
    char symbol;
    while (true)
    {
        std::cout << "Choisissez un symbole (un seul caractere, ex: X ou O) : ";
        std::cin >> symbol;
        if (!std::cin.fail() && (symbol == 'X' || symbol == 'O' || symbol == 'x' || symbol == 'o'))
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return toupper(symbol);
        } else {
            std::cout << "Entree invalide, recommencez.\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Player createPlayer()
{
    Player player{};
    player.isAI = false;
    player.name = askName();
    player.symbol = askSymbol();
    return player;
}

Player createPlayer(char symbol)
{
    Player player{};
    player.isAI = false;
    player.name = askName();
    player.symbol = symbol;
    return player;
}

Player createAIPlayer(char symbol)
{
    Player ai{};
    ai.name = "IA";
    ai.symbol = symbol;
    ai.isAI  = true;
    return ai;
}
