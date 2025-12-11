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

static char askColor()
{
    char color;
    while (true)
    {
        std::cout << "Choisissez une couleur jaune ou rouge (un seul caractere, ex: J ou R) : ";
        std::cin >> color;
        if (!std::cin.fail() && (color == 'J' || color == 'R' || color == 'j' || color == 'r'))
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return toupper(color);
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
    player.name = askName();
    player.color = askColor();
    return player;
}

Player createPlayer(char color)
{
    Player player{};
    player.name = askName();
    player.color = color;
    return player;
}