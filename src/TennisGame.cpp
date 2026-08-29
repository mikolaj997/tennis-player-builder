#include "TennisGame.h"

#include <iostream>

void TennisGame::addPlayer(const std::string &name)
{
    players.emplace_back(
        name,
        90, // forehand
        90, // backhand
        90, // serve
        90, // volley
        90, // drop shot
        90, // stamina
        90  // mental strength
    );
}

void TennisGame::showPlayers() const
{
    for (const TennisPlayer &player : players)
    {
        std::cout << player.getName() << '\n';
    }
}