#include "TennisGame.h"

int main()
{
    TennisGame game;

    game.addPlayer("Carlos Alcaraz", 95, 91, 90, 88, 94, 93, 92);
    game.addPlayer("Novak Djokovic", 94, 98, 95, 93, 91, 96, 99);
    game.addPlayer("Jannik Sinner", 96, 94, 92, 87, 90, 94, 91);
    game.addPlayer("Alexander Zverev", 91, 93, 96, 85, 86, 92, 89);
    game.addPlayer("Daniil Medvedev", 88, 95, 94, 82, 89, 96, 91);
    game.addPlayer("Andrey Rublev", 94, 87, 92, 80, 85, 90, 86);
    game.addPlayer("Taylor Fritz", 93, 88, 95, 83, 84, 89, 87);
    game.addPlayer("Holger Rune", 90, 91, 89, 86, 88, 87, 88);
    game.addPlayer("Alex de Minaur", 87, 90, 84, 89, 86, 97, 91);
    game.addPlayer("Ben Shelton", 92, 84, 97, 78, 82, 86, 84);

    game.startGame();

    return 0;
}