#include "TennisGame.h"

#include <iostream>
#include <random>

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

    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(players.size()) - 1);

    int randomIndex = distribution(generator);

    std::cout << "\nRandom player:\n";
    std::cout << players[randomIndex].getName() << "\n\n";

    std::cout << "Choose an attribute:\n";

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
    case 1:
        if (!forehandTaken)
        {
            forehandTaken = true;
            std::cout << "Forehand assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 2:
        if (!backhandTaken)
        {
            backhandTaken = true;
            std::cout << "Backhand assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 3:
        if (!serveTaken)
        {
            serveTaken = true;
            std::cout << "Serve assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 4:
        if (!volleyTaken)
        {
            volleyTaken = true;
            std::cout << "Volley assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 5:
        if (!dropShotTaken)
        {
            dropShotTaken = true;
            std::cout << "Drop Shot assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 6:
        if (!staminaTaken)
        {
            staminaTaken = true;
            std::cout << "Stamina assigned to "
                      << players[randomIndex].getName() << "\n";
        }
        break;

    case 7:
        if (!mentalStrengthTaken)
        {
            mentalStrengthTaken = true;
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

    while (currentRound < 7)
    {
        ++currentRound;

        std::cout << "\n=== ROUND "
                  << currentRound
                  << " ===\n";

        startSelection();
    }

    std::cout << "\n=== GAME OVER ===\n";
}