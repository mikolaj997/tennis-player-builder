#pragma once

#include "TennisPlayer.h"

#include <vector>

class TennisGame
{
private:
    std::vector<TennisPlayer> players;
    std::vector<bool> playerUsed;

    TennisPlayer *selectedForehand = nullptr;
    TennisPlayer *selectedBackhand = nullptr;
    TennisPlayer *selectedServe = nullptr;
    TennisPlayer *selectedVolley = nullptr;
    TennisPlayer *selectedDropShot = nullptr;
    TennisPlayer *selectedStamina = nullptr;
    TennisPlayer *selectedMentalStrength = nullptr;

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

    int calculateRating() const;

    void showPlayers() const;
    void startGame();
    void startSelection();
    void startTiebreaker(TennisGame &other);
    void showPlayerSummary() const;

private:
    int chooseTiebreakerPlayer(const std::string &attribute);
    int pickRandomPlayerRating(const std::string &attribute) const;
    bool hasAvailablePlayers() const;
};