#include "TennisGame.h"

int main() {
    TennisGame game;

    game.addPlayer("Carlos Alcaraz", 95, 91, 90, 88, 94, 93, 92);
    game.addPlayer("Novak Djokovic", 94, 98, 95, 93, 91, 96, 99);
    game.addPlayer("Jannik Sinner", 96, 94, 92, 87, 90, 94, 91);

    game.startSelection();

    return 0;
}