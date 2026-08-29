#pragma once

#include "TennisPlayer.h"
#include <vector>

class TennisGame {
private:
    std::vector<TennisPlayer> players;

public:
    void addPlayer(const std::string& name);
    void showPlayers() const;
};