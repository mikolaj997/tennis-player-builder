#include "TennisGame.h"
#include "ConsoleInput.h"

#include <iostream>
#include <random>
#include <algorithm>

void TennisGame::addPlayer(
    const std::string &name,
    int forehand,
    int backhand,
    int serve,
    int volley,
    int dropShot,
    int stamina,
    int mentalStrength)
{
    players.emplace_back(
        name,
        forehand,
        backhand,
        serve,
        volley,
        dropShot,
        stamina,
        mentalStrength);

    playerUsed.push_back(false);
}

bool TennisGame::prepareRound()
{
    if (isComplete() || pendingPlayer)
        return !isComplete();

    std::vector<std::size_t> availablePlayers;
    for (std::size_t i = 0; i < players.size(); ++i)
    {
        if (!playerUsed[i])
            availablePlayers.push_back(i);
    }

    if (availablePlayers.empty())
        return false;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<std::size_t> distribution(0, availablePlayers.size() - 1);
    pendingPlayer = availablePlayers[distribution(generator)];
    return true;
}

bool TennisGame::selectAttribute(Attribute attribute)
{
    if (!pendingPlayer || !attributeAvailable(attribute))
        return false;

    const auto attributeIndex = static_cast<std::size_t>(attribute);
    selectedPlayers[attributeIndex] = *pendingPlayer;
    playerUsed[*pendingPlayer] = true;
    pendingPlayer.reset();
    return true;
}

bool TennisGame::skipRound()
{
    if (!pendingPlayer || skipsLeft() <= 0)
        return false;

    playerUsed[*pendingPlayer] = true;
    ++skipsUsed;
    pendingPlayer.reset();
    return true;
}

bool TennisGame::isComplete() const
{
    return std::find(selectedPlayers.begin(), selectedPlayers.end(), std::nullopt) == selectedPlayers.end();
}

bool TennisGame::isRoundReady() const
{
    return pendingPlayer.has_value();
}

std::string TennisGame::pendingPlayerName() const
{
    return pendingPlayer ? players[*pendingPlayer].getName() : std::string{};
}

int TennisGame::skipsLeft() const
{
    std::size_t availableCount = 0;
    for (const bool used : playerUsed)
    {
        if (!used)
            ++availableCount;
    }

    const auto remainingAttributes = std::count(selectedPlayers.begin(), selectedPlayers.end(), std::nullopt);
    const auto remaining = static_cast<std::size_t>(remainingAttributes);
    const int sparePlayers = availableCount > remaining ? static_cast<int>(availableCount - remaining) : 0;
    return std::min(maxSkips - skipsUsed, sparePlayers);
}

bool TennisGame::attributeAvailable(Attribute attribute) const
{
    const auto attributeIndex = static_cast<std::size_t>(attribute);
    return attributeIndex < selectedPlayers.size() && !selectedPlayers[attributeIndex];
}

void TennisGame::startSelection()
{
    if (players.empty())
    {
        std::cout << "No players available.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    std::vector<std::size_t> availablePlayers;

    for (std::size_t i = 0; i < players.size(); ++i)
    {
        if (!playerUsed[i])
        {
            availablePlayers.push_back(i);
        }
    }
    if (availablePlayers.empty())
    {
        std::cout << "No players left to choose from.\n";
        return;
    }

    const int remainingSkips = skipsLeft();
    const bool canSkip = remainingSkips > 0;

    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(availablePlayers.size()) - 1);

    const auto randomIndex = availablePlayers[distribution(generator)];

    std::cout << "\nRandom player:\n";
    std::cout << players[randomIndex].getName() << "\n\n";

    std::cout << "Choose an attribute:\n";
    std::cout << "Skips left: " << remainingSkips << "\n";

    if (canSkip)
        std::cout << "0. Skip\n";
    for (std::size_t i = 0; i < attributeCount; ++i)
    {
        if (!selectedPlayers[i])
            std::cout << i + 1 << ". " << attributeNames[i] << "\n";
    }

    int choice;
    std::cout << "Choose: ";
    while (true)
    {
        if (!readChoice(choice, 0, static_cast<int>(attributeCount)))
            return;
        if (choice == 0 && !canSkip)
        {
            std::cout << "No skips left. Choose an attribute: ";
            continue;
        }
        if (choice > 0 && selectedPlayers[choice - 1])
        {
            std::cout << "Attribute already taken. Choose another attribute: ";
            continue;
        }
        break;
    }

    playerUsed[randomIndex] = true;

    if (choice == 0)
    {
        ++skipsUsed;
        std::cout << "Player skipped.\n";
        return;
    }
    selectedPlayers[choice - 1] = randomIndex;
    std::cout << attributeName(static_cast<Attribute>(choice - 1)) << " assigned to "
              << players[randomIndex].getName() << "\n";
}

bool TennisGame::startGame()
{
    currentRound = 0;
    while (std::find(selectedPlayers.begin(), selectedPlayers.end(), std::nullopt) != selectedPlayers.end())
    {
        if (!hasAvailablePlayers())
        {
            std::cout << "Not enough players to complete the selection.\n";
            return false;
        }
        std::cout << "\n=== ROUND " << ++currentRound << " ===\n";
        startSelection();
        if (!std::cin)
            return false;
    }
    std::cout << "\n=== GAME OVER ===\n";
    showPlayerSummary();
    std::cout << "\nFinal rating: " << calculateRating() << "\n";
    return true;
}

void TennisGame::showPlayerSummary() const
{
    for (const auto &line : playerSummaryLines())
        std::cout << line << '\n';
}

std::vector<std::string> TennisGame::playerSummaryLines() const
{
    std::vector<std::string> lines{"=== YOUR PLAYER ==="};
    for (std::size_t i = 0; i < attributeCount; ++i)
    {
        std::string line = std::string(attributeNames[i]) + ": ";
        if (selectedPlayers[i])
            line += players[*selectedPlayers[i]].getName();
        lines.push_back(line);
    }
    return lines;
}

int TennisGame::calculateRating() const
{
    int total = 0;
    for (std::size_t i = 0; i < attributeCount; ++i)
        total += players.at(selectedPlayers[i].value()).getRating(static_cast<Attribute>(i));
    return total / static_cast<int>(attributeCount);
}

bool TennisGame::hasAvailablePlayers() const
{
    return std::find(playerUsed.begin(), playerUsed.end(), false) != playerUsed.end();
}

int TennisGame::chooseTiebreakerPlayer(Attribute attribute)
{
    std::vector<std::size_t> availablePlayers;
    for (std::size_t i = 0; i < players.size(); ++i)
    {
        if (!playerUsed[i])
            availablePlayers.push_back(i);
    }
    int choice;
    if (!readChoice(choice, 1, static_cast<int>(availablePlayers.size())))
        return 0;
    const auto selectedIndex = availablePlayers[choice - 1];
    playerUsed[selectedIndex] = true;
    std::cout << players[selectedIndex].getName() << " selected.\n";
    return players[selectedIndex].getRating(attribute);
}
int TennisGame::pickRandomPlayerRating(Attribute attribute) const
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(players.size()) - 1);

    int randomIndex = distribution(generator);
    int rating = players[randomIndex].getRating(attribute);

    std::cout << players[randomIndex].getName()
              << " drawn from the full pool.\n";

    return rating;
}

void TennisGame::startTiebreaker(TennisGame &other)
{
    std::cout << "\n=== TIEBREAKER ===\n";

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> attributeDistribution(
        0,
        static_cast<int>(attributeCount) - 1);

    bool decided = false;

    while (!decided)
    {
        bool player1HasPlayers = hasAvailablePlayers();
        bool player2HasPlayers = other.hasAvailablePlayers();

        if (!player1HasPlayers && player2HasPlayers)
        {
            std::cout << "\nPlayer 1 has no players left to choose from. Player 2 wins!\n";
            return;
        }

        if (!player2HasPlayers && player1HasPlayers)
        {
            std::cout << "\nPlayer 2 has no players left to choose from. Player 1 wins!\n";
            return;
        }

        const auto attribute = static_cast<Attribute>(attributeDistribution(generator));

        std::cout << "\nTiebreaker attribute: " << attributeName(attribute) << "\n";

        int value1;
        int value2;

        if (!player1HasPlayers && !player2HasPlayers)
        {
            std::cout << "Both benches are empty - drawing one player from the full pool for each.\n";

            std::cout << "\n--- Player 1 ---\n";
            value1 = pickRandomPlayerRating(attribute);

            std::cout << "\n--- Player 2 ---\n";
            value2 = other.pickRandomPlayerRating(attribute);
        }
        else
        {
            auto playerLines = [](const TennisGame &game, const char *title)
            {
                std::vector<std::string> lines{"=== " + std::string(title) + " ==="};
                std::size_t number = 1;
                for (std::size_t i = 0; i < game.players.size(); ++i)
                {
                    if (!game.playerUsed[i])
                    {
                        lines.push_back(std::to_string(number++) + ". " +
                                        game.players[i].getName());
                    }
                }
                return lines;
            };

            const auto left = playerLines(*this, "PLAYER 1");
            const auto right = playerLines(other, "PLAYER 2");
            constexpr std::size_t panelWidth = 52;
            const auto lineCount = std::max(left.size(), right.size());
            for (std::size_t i = 0; i < lineCount; ++i)
            {
                const std::string leftLine = i < left.size() ? left[i] : "";
                const std::string rightLine = i < right.size() ? right[i] : "";
                std::cout << leftLine.substr(0, panelWidth);
                if (leftLine.size() < panelWidth)
                    std::cout << std::string(panelWidth - leftLine.size(), ' ');
                std::cout << " | " << rightLine << '\n';
            }

            std::cout << "\nChoose Player 1 for " << attributeName(attribute) << ": ";
            value1 = chooseTiebreakerPlayer(attribute);
            if (!std::cin)
                return;

            std::cout << "\nChoose Player 2 for " << attributeName(attribute) << ": ";
            value2 = other.chooseTiebreakerPlayer(attribute);
            if (!std::cin)
                return;
        }

        std::cout << "\nComparing " << attributeName(attribute) << ": "
                  << value1 << " vs " << value2 << "\n";

        if (value1 > value2)
        {
            std::cout << "Winner (tiebreaker): Player 1\n";
            decided = true;
        }
        else if (value2 > value1)
        {
            std::cout << "Winner (tiebreaker): Player 2\n";
            decided = true;
        }
        else
        {
            std::cout << "Still tied on this attribute. Another round...\n";
        }
    }
}
