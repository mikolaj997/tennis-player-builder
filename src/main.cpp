#include "TennisGame.h"

int main() {
    TennisGame game;

    game.addPlayer("Carlos Alcaraz");
    game.addPlayer("Novak Djokovic");
    game.addPlayer("Jannik Sinner");

    game.showPlayers();

    return 0;
}