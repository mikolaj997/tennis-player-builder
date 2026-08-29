#include "TennisGame.h"

#include <iostream>

void TennisGame::addPlayer(const std::string& name) {
    players.emplace_back(name);
}

void TennisGame::showPlayers() const {
    for (const TennisPlayer& player : players) {
        std::cout << player.getName() << '\n';
    }
}