# 🎮 Tic-Tac-Toe (et Puissance 4) – Rapport de projet

Projet individuel dans le cadre du cours de Programmation et Algorithmique (IMAC3).  
Le dépôt contient deux jeux jouables en console :

- `TicTacToe/` : jeu de morpion (3x3), mode 2 joueurs ou joueur vs IA.
- `Pow4/` : jeu de Puissance 4 (6x7), mode 2 joueurs.

## Prérequis & exécution

### Environnement général

| Élément                          | Détail                                                              |
| -------------------------------- | ------------------------------------------------------------------- |
| **Langage**                      | C++17                                                               |
| **Outil de build**               | CMake ≥ 3.10                                                        |
| **Compilateur testé**            | MSVC (Visual Studio)                                                |
| **Système d’exploitation testé** | Windows 11                                                          |
| **Librairies externes**          | Aucune (uniquement la STL et `<windows.h>` pour la console Windows) |

<div style="background-color: #fff3cd; border-left: 4px solid #ffc107; padding: 10px; margin: 10px 0; border-radius: 5px; font-family: Arial, sans-serif; color: #856404;">💡 Le code utilise des séquences ANSI pour les couleurs et `windows.h` pour le réglage de l’UTF-8 dans la console. Sous Linux/macOS, il faudra adapter ou retirer ces appels spécifiques à Windows.</div>

---

### Compilation & exécution – Tic-Tac-Toe

- Lancez le CMake du dossier `TicTacToe`
- Sous Windows : exécutable généré : `TicTacToe.exe`

Le programme ouvre un menu qui permet de choisir :

- Mode\*2 joueurs.
- Mode joueur vs IA.
- Symboles et nom des joueurs.
- Rejouer une partie sans relancer le programme.

---

### Compilation & exécution – Puissance 4

- Lancez le CMake du dossier `Pow4`
- Sous Windows : exécutable généré : `Pow4.exe`

Le programme :

- Demande les noms des joueurs.
- Demande la couleur (Jaune / Rouge).
- Tire aléatoirement le premier joueur.
- Boucle de jeu.
- Rejouer une partie sans relancer le programme.

## Organisation du code

### Vue d’ensemble du dépôt

```text
.
├── Pow4/
│   ├── CMakeLists.txt
│   ├── include/
│   │   ├── Board.hpp
│   │   ├── Game.hpp
│   │   └── Player.hpp
│   └── src/
│       ├── Board.cpp
│       ├── Game.cpp
│       ├── Player.cpp
│       └── main.cpp
├── TicTacToe/
│   ├── CMakeLists.txt
│   ├── include/
│   │   ├── Board.hpp
│   │   ├── Game.hpp
│   │   └── Player.hpp
│   └── src/
│       ├── Board.cpp
│       ├── Game.cpp
│       ├── Player.cpp
│       └── main.cpp
├── .gitattributes
├── .gitignore
└── README.md   # Ce rapport
```

---

## Organisation & choix d’implémentation

### Modélisation commune

Les deux jeux partagent une architecture très similaire, organisée autour de trois entités :

| Concept  | Rôle                                                               |
| -------- | ------------------------------------------------------------------ |
| `Board`  | Représentation du plateau, vérification des coups et des victoires |
| `Player` | Informations sur le joueur (nom, symbole / couleur, IA ou non)     |
| `Game`   | Logique métier : boucle de jeu, gestion des tours, fin de partie   |

Cette organisation rend le code lisible, modulaire et facilement extensible.

---

### Détail du projet

| Fichier / Module                        | Description                                                                                                         |
| --------------------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| `include/Board.hpp` / `src/Board.cpp`   | Plateau 3x3 stocké dans un `std::array<char, 9>`. Affichage, validation de coups, détection de victoire ou égalité. |
| `include/Player.hpp` / `src/Player.cpp` | Structure `Player` (`name`, `symbol`, `isAI`). Fonctions de création de joueurs humains ou IA.                      |
| `include/Game.hpp` / `src/Game.cpp`     | Enum `GameMode` (2 joueurs / vs IA), logique de partie, boucle principale, IA.                                      |
| `src/main.cpp`                          | Point d’entrée : configuration console (UTF-8), boucle pour rejouer, appel de `Game`.                               |

### Choix notables :

- Le plateau stocke les positions `'1'` à `'9'` au départ pour aider l’utilisateur à visualiser rapidement les cases disponibles.
- Les fonctions de vérification de victoire (`Board::verifyWin`) utilisent la dernière position jouée et parcourent les lignes / colonnes / diagonales pour limiter le nombre de tests.
- Le code de gestion d’entrée utilisateur est robuste : nettoyage du buffer et boucles tant que l’entrée n’est pas valide.

## Améliorations et fonctionnalités supplémentaires

| Fonctionnalité supplémentaire      | Description                                                                                                                            | Utilisation                                                      |
| ---------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------- |
| IA "intelligente" (`chooseAIMove`) | L’IA joue de manière “intelligente” : coup gagnant, blocage, stratégie<span style="color:rgb(255, 0, 25); font-weight:bold;">\*</span> | Automatique en mode IA.                                          |
| Validation robuste des entrées     | Gestion des erreurs de saisie, caractères invalides, etc                                                                               | Entrées clavier : position, symbole, rejouer, etc.               |
| ASCII art & couleurs console       | Titre stylisé “TIC TAC TOE”, texte coloré, meilleure lisibilité                                                                        | Visible dès `Game::initGame()`.                                  |
| Boucle de rejouabilité             | Possibilité de relancer une partie sans quitter le programme                                                                           | Question “Voulez-vous jouer à nouveau ? (o/n)” en fin de partie. |
| Puissance 4                        | Jeu du puissance 4 avec choix de la couleur, interface stylisée, etc...                                                                | Lancer `Pow4.exe` en effectuant le build                         |

### <span style="color:rgb(255, 0, 25); font-weight:bold;">\*</span> Détail de l’IA :

L’IA suit plusieurs étapes pour choisir un coup :

1. **Chercher un coup gagnant** : tester chaque position libre et voir si elle mène à une victoire de l’IA.
2. **Bloquer le joueur** : si le joueur peut gagner au prochain coup, jouer à cet endroit.
3. **Favoriser des positions stratégiques** : centre, lignes/colonnes sans symbole adverse, etc.
4. **Sinon** : choisir aléatoirement parmi les positions restantes en faisant les coups les plus intéressant (centre --> coins --> cotés).

## Problèmes rencontrés et solutions

### 1. Détection des conditions de victoire

- **Problème** : coder la victoire naïvement pour chaque direction devenait rapidement verbeux et sources d’erreurs (surtout pour Puissance 4).
- **Solution** :
  - Factorisation de la logique dans des fonctions dédiées :
    - Tic-Tac-Toe : `Board::verifyWin(position, symbol, predictive)`.
    - Puissance 4 : `Board::countInDirection(...)` + `Board::verifyWin(...)`.
  - Utilisation systématique de la dernière case jouée pour réduire les vérifications nécessaires.
  - On analyse que les cases nécessaires :
    - Tic-Tac-Toe : on regarde la ligne, colonne, ou diagonale sur laquelle se trouve le dernier coup jouer
    - Puissance 4 : on compte les symboles à proximité en vérifiant la continuité et en faisant dans les 4 directions possibles (8 plus exactement)

## Bilan rapide

- Objectifs du projet atteints : deux jeux jouables en console (Tic-Tac-Toe & Puissance 4) dont une avec IA. (Soit 2 améliorations faites)
- Code structuré et modulable (séparation claire `Board` / `Player` / `Game`).
- Amélioration de l'UI/UX avec les couleurs dans le terminal, etc...
- 🔁 Pistes d’amélioration possibles :
  - Rendre le code totalement portable (supprimer la dépendance à `windows.h`).
  - Ajouter un système de score ou un menu unique pour choisir entre les deux jeux.

<div align="center" style="margin-top: 50px; font-size: 1em; font-weight:bold;">Kellian Bredeau</div>
