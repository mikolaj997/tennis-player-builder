#pragma once

#include "TennisPlayer.h"

#include <vector>
#include <optional>

class TennisGame
{
private:
    std::vector<TennisPlayer> players;
    std::vector<bool> playerUsed;

    std::array<std::optional<std::size_t>, attributeCount> selectedPlayers{};

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
    bool startGame();
    void startSelection();
    void startTiebreaker(TennisGame &other);
    void showPlayerSummary() const;

private:
    int chooseTiebreakerPlayer(Attribute attribute);
    int pickRandomPlayerRating(Attribute attribute) const;
    bool hasAvailablePlayers() const;
};
