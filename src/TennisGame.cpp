#include "TennisGame.h"

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

void TennisGame::startSelection()
{
    if (players.empty())
    {
        std::cout << "No players available.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    std::vector<int> availablePlayers;

    for (int i = 0; i < players.size(); ++i)
    {
        if (!playerUsed[i])
        {
            availablePlayers.push_back(i);
        }
    }
    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(availablePlayers.size()) - 1);

    int randomIndex = availablePlayers[distribution(generator)];

    playerUsed[randomIndex] = true;
    std::cout << "\nRandom player:\n";
    std::cout << players[randomIndex].getName() << "\n\n";

    std::cout << "Choose an attribute:\n";

    std::cout << "0. Skip\n";
    if (!forehandTaken)
        std::cout << "1. Forehand\n";

    if (!backhandTaken)
        std::cout << "2. Backhand\n";

    if (!serveTaken)
        std::cout << "3. Serve\n";

    if (!volleyTaken)
        std::cout << "4. Volley\n";

    if (!dropShotTaken)
        std::cout << "5. Drop Shot\n";

    if (!staminaTaken)
        std::cout << "6. Stamina\n";

    if (!mentalStrengthTaken)
        std::cout << "7. Mental Strength\n";

    int choice;
    std::cout << "Choose: ";
    std::cin >> choice;

    switch (choice)
    {
    case 0:
        std::cout << "Player skipped.\n";
        break;
    case 1:
        if (!forehandTaken)
        {
            forehandTaken = true;
            selectedForehand = &players[randomIndex];

            std::cout << "Forehand assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 2:
        if (!backhandTaken)
        {
            backhandTaken = true;
            selectedBackhand = &players[randomIndex];

            std::cout << "Backhand assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 3:
        if (!serveTaken)
        {
            serveTaken = true;
            selectedServe = &players[randomIndex];

            std::cout << "Serve assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 4:
        if (!volleyTaken)
        {
            volleyTaken = true;
            selectedVolley = &players[randomIndex];

            std::cout << "Volley assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 5:
        if (!dropShotTaken)
        {
            dropShotTaken = true;
            selectedDropShot = &players[randomIndex];

            std::cout << "Drop Shot assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 6:
        if (!staminaTaken)
        {
            staminaTaken = true;
            selectedStamina = &players[randomIndex];

            std::cout << "Stamina assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 7:
        if (!mentalStrengthTaken)
        {
            mentalStrengthTaken = true;
            selectedMentalStrength = &players[randomIndex];

            std::cout << "Mental Strength assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    default:
        std::cout << "Invalid choice.\n";
    }
}
void TennisGame::startGame()
{
    currentRound = 0;

    while (
        !forehandTaken ||
        !backhandTaken ||
        !serveTaken ||
        !volleyTaken ||
        !dropShotTaken ||
        !staminaTaken ||
        !mentalStrengthTaken)
    {
        ++currentRound;

        std::cout << "\n=== ROUND "
                  << currentRound
                  << " ===\n";

        startSelection();
    }

    std::cout << "\n=== GAME OVER ===\n";
    showPlayerSummary();
    std::cout << "\nFinal rating: "
              << calculateRating()
              << "\n";
}
void TennisGame::showPlayerSummary() const
{
    std::cout << "\n=== YOUR PLAYER ===\n";

    std::cout << "Forehand: ";
    if (selectedForehand != nullptr)
        std::cout << selectedForehand->getName() << '\n';

    std::cout << "Backhand: ";
    if (selectedBackhand != nullptr)
        std::cout << selectedBackhand->getName() << '\n';

    std::cout << "Serve: ";
    if (selectedServe != nullptr)
        std::cout << selectedServe->getName() << '\n';

    std::cout << "Volley: ";
    if (selectedVolley != nullptr)
        std::cout << selectedVolley->getName() << '\n';

    std::cout << "Drop Shot: ";
    if (selectedDropShot != nullptr)
        std::cout << selectedDropShot->getName() << '\n';

    std::cout << "Stamina: ";
    if (selectedStamina != nullptr)
        std::cout << selectedStamina->getName() << '\n';

    std::cout << "Mental Strength: ";
    if (selectedMentalStrength != nullptr)
        std::cout << selectedMentalStrength->getName() << '\n';
}
int TennisGame::calculateRating() const
{
    int total = 0;

    total += selectedForehand->getRating("forehand");
    total += selectedBackhand->getRating("backhand");
    total += selectedServe->getRating("serve");
    total += selectedVolley->getRating("volley");
    total += selectedDropShot->getRating("dropShot");
    total += selectedStamina->getRating("stamina");
    total += selectedMentalStrength->getRating("mentalStrength");

    return total / 7;
}
bool TennisGame::hasAvailablePlayers() const
{
    for (bool used : playerUsed)
    {
        if (!used)
        {
            return true;
        }
    }
    return false;
}

int TennisGame::chooseTiebreakerPlayer(const std::string &attribute)
{
    std::vector<int> availablePlayers;

    for (int i = 0; i < players.size(); ++i)
    {
        if (!playerUsed[i])
        {
            availablePlayers.push_back(i);
        }
    }

    std::cout << "\nChoose a player for " << attribute << ":\n";

    for (size_t i = 0; i < availablePlayers.size(); ++i)
    {
        int playerIndex = availablePlayers[i];

        std::cout << i + 1 << ". "
                  << players[playerIndex].getName()
                  << "\n";
    }

    int choice;

    std::cout << "Choose: ";
    std::cin >> choice;

    while (choice < 1 || choice > static_cast<int>(availablePlayers.size()))
    {
        std::cout << "Invalid choice. Choose again: ";
        std::cin >> choice;
    }

    int selectedIndex = availablePlayers[choice - 1];
    playerUsed[selectedIndex] = true;

    std::cout << players[selectedIndex].getName() << " selected.\n";

    return players[selectedIndex].getRating(attribute);
}

int TennisGame::pickRandomPlayerRating(const std::string &attribute) const
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

    std::vector<std::string> attributes = {
        "forehand",
        "backhand",
        "serve",
        "volley",
        "dropShot",
        "stamina",
        "mentalStrength"};

    std::uniform_int_distribution<int> attributeDistribution(
        0,
        static_cast<int>(attributes.size()) - 1);

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

        const std::string &attribute = attributes[attributeDistribution(generator)];

        std::cout << "\nTiebreaker attribute: " << attribute << "\n";

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
            std::cout << "\n--- Player 1 ---\n";
            value1 = chooseTiebreakerPlayer(attribute);

            std::cout << "\n--- Player 2 ---\n";
            value2 = other.chooseTiebreakerPlayer(attribute);
        }

        std::cout << "\nComparing " << attribute << ": "
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