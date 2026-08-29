#pragma once

#include "TennisPlayer.h"

#include <vector>

class TennisGame
{
private:
    std::vector<TennisPlayer> players;

    bool forehandTaken = false;
    bool backhandTaken = false;
    bool serveTaken = false;
    bool volleyTaken = false;
    bool dropShotTaken = false;
    bool staminaTaken = false;
    bool mentalStrengthTaken = false;

    int currentRound = 0;

public:
    void addPlayer(
        const std::string &name,
        int forehand,
        int backhand,
        int serve,
        int volley,
        int dropShot,
        int stamina,
        int mentalStrength);

    void showPlayers() const;
    void startGame();
    void startSelection();
};