#include "TennisGame.h"
#include "ConsoleInput.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <array>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

struct KeyBinding
{
    int key;
    Attribute attribute;
};

const std::array<KeyBinding, attributeCount> playerOneKeys = {{{'A', Attribute::Forehand},
                                                               {'S', Attribute::Backhand},
                                                               {'D', Attribute::Serve},
                                                               {'F', Attribute::Volley},
                                                               {'Q', Attribute::DropShot},
                                                               {'W', Attribute::Stamina},
                                                               {'E', Attribute::MentalStrength}}};

const std::array<KeyBinding, attributeCount> playerTwoKeys = {{{'H', Attribute::Forehand},
                                                               {'J', Attribute::Backhand},
                                                               {'K', Attribute::Serve},
                                                               {'L', Attribute::Volley},
                                                               {'Y', Attribute::DropShot},
                                                               {'U', Attribute::Stamina},
                                                               {'I', Attribute::MentalStrength}}};

std::vector<std::string> makeDraftPanel(const char *title, const TennisGame &game,
                                        const std::array<KeyBinding, attributeCount> &keys,
                                        int skipKey, bool submitted)
{
    std::vector<std::string> lines{"=== " + std::string(title) + " ==="};
    if (game.isComplete())
    {
        lines.push_back("Draft complete. Waiting for the other player.");
        return lines;
    }

    if (submitted)
    {
        lines.push_back("Move accepted. Waiting for the other player.");
        return lines;
    }

    lines.push_back("Random player: " + game.pendingPlayerName());
    lines.push_back("Skips left: " + std::to_string(game.skipsLeft()) +
                    " (" + static_cast<char>(skipKey) + ")");
    for (std::size_t i = 0; i < attributeCount; ++i)
    {
        std::string line = std::string(1, static_cast<char>(keys[i].key)) +
                           " - " + attributeNames[i];
        if (!game.attributeAvailable(keys[i].attribute))
            line += " [assigned]";
        lines.push_back(line);
    }
    return lines;
}

void showDraftPanels(const TennisGame &playerOne, const TennisGame &playerTwo,
                     bool playerOneSubmitted, bool playerTwoSubmitted)
{
    const auto left = makeDraftPanel("PLAYER 1", playerOne, playerOneKeys, 'R', playerOneSubmitted);
    const auto right = makeDraftPanel("PLAYER 2", playerTwo, playerTwoKeys, 'O', playerTwoSubmitted);
    const auto lineCount = std::max(left.size(), right.size());
    constexpr std::size_t panelWidth = 52;

    std::cout << '\n';
    for (std::size_t i = 0; i < lineCount; ++i)
    {
        const std::string leftLine = i < left.size() ? left[i] : "";
        const std::string rightLine = i < right.size() ? right[i] : "";
        std::cout << leftLine.substr(0, panelWidth);
        if (leftLine.size() < panelWidth)
            std::cout << std::string(panelWidth - leftLine.size(), ' ');
        std::cout << " | " << rightLine << '\n';
    }
}

void showResultPanels(const TennisGame &playerOne, const TennisGame &playerTwo,
                      int ratingOne, int ratingTwo)
{
    auto left = playerOne.playerSummaryLines();
    auto right = playerTwo.playerSummaryLines();
    left[0] = "=== PLAYER 1 ===";
    right[0] = "=== PLAYER 2 ===";
    constexpr std::size_t panelWidth = 52;
    const auto lineCount = std::max(left.size(), right.size());

    std::cout << "\n=== RESULT ===\n";
    for (std::size_t i = 0; i < lineCount; ++i)
    {
        const std::string leftLine = i < left.size() ? left[i] : "";
        const std::string rightLine = i < right.size() ? right[i] : "";
        std::cout << leftLine.substr(0, panelWidth);
        if (leftLine.size() < panelWidth)
            std::cout << std::string(panelWidth - leftLine.size(), ' ');
        std::cout << " | " << rightLine << '\n';
    }

    std::cout << "\nPlayer 1 rating: " << ratingOne
              << "                 | Player 2 rating: " << ratingTwo << '\n';
}

#ifdef _WIN32
int readDraftKey()
{
    static std::array<bool, 256> wasDown{};
    const std::array<int, 17> keys = {
        VK_ESCAPE, 'A', 'S', 'D', 'F', 'Q', 'W', 'E',
        'R', 'H', 'J', 'K', 'L', 'Y', 'U', 'I', 'O'};

    while (true)
    {
        for (const int key : keys)
        {
            const bool isDown = (GetAsyncKeyState(key) & 0x8000) != 0;
            const bool pressed = isDown && !wasDown[key];
            wasDown[key] = isDown;
            if (pressed)
                return key;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
#else
int readDraftKey()
{
    char key;
    if (!std::cin.get(key))
        return 27;
    return key >= 'a' && key <= 'z' ? key - ('a' - 'A') : key;
}
#endif

bool handleDraftKey(TennisGame &game, int key,
                    const std::array<KeyBinding, attributeCount> &bindings,
                    int skipKey)
{
    if (key == skipKey)
        return game.skipRound();

    for (const auto &binding : bindings)
    {
        if (key == binding.key)
            return game.selectAttribute(binding.attribute);
    }
    return false;
}

bool startTwoPlayerDraft(TennisGame &playerOne, TennisGame &playerTwo)
{
    bool playerOneSubmitted = false;
    bool playerTwoSubmitted = false;

    while (!playerOne.isComplete() || !playerTwo.isComplete())
    {
        if (!playerOne.isComplete() && !playerOneSubmitted && !playerOne.isRoundReady() && !playerOne.prepareRound())
            return false;
        if (!playerTwo.isComplete() && !playerTwoSubmitted && !playerTwo.isRoundReady() && !playerTwo.prepareRound())
            return false;

        std::cout << "\x1b[2J\x1b[H";
        std::cout << "=== TWO PLAYER DRAFT ===\n";
        showDraftPanels(playerOne, playerTwo, playerOneSubmitted, playerTwoSubmitted);
        std::cout << "\nPress Escape to exit.\n";

        const int key = readDraftKey();
        if (key == 27)
            return false;

        if (!playerOneSubmitted && !playerOne.isComplete())
        {
            if (handleDraftKey(playerOne, key, playerOneKeys, 'R'))
                playerOneSubmitted = true;
        }
        if (!playerTwoSubmitted && !playerTwo.isComplete())
        {
            if (handleDraftKey(playerTwo, key, playerTwoKeys, 'O'))
                playerTwoSubmitted = true;
        }

        if ((playerOneSubmitted || playerOne.isComplete()) &&
            (playerTwoSubmitted || playerTwo.isComplete()))
        {
            playerOneSubmitted = false;
            playerTwoSubmitted = false;
        }
    }

    return true;
}

void loadPlayers(TennisGame &game)
{
    game.addPlayer("Carlos Alcaraz", 95, 91, 90, 88, 94, 93, 92);
    game.addPlayer("Novak Djokovic", 94, 98, 95, 93, 91, 96, 99);
    game.addPlayer("Jannik Sinner", 96, 94, 92, 87, 90, 94, 91);
    game.addPlayer("Alexander Zverev", 91, 93, 96, 85, 86, 92, 89);
    game.addPlayer("Daniil Medvedev", 88, 95, 94, 82, 89, 96, 91);
    game.addPlayer("Andrey Rublev", 94, 87, 92, 80, 85, 90, 86);
    game.addPlayer("Taylor Fritz", 93, 88, 95, 83, 84, 89, 87);
    game.addPlayer("Holger Rune", 90, 91, 89, 86, 88, 87, 88);
    game.addPlayer("Alex de Minaur", 87, 90, 84, 89, 86, 97, 91);
    game.addPlayer("Ben Shelton", 92, 84, 97, 78, 82, 86, 84);
}

int main()
{
    int mode;

    std::cout << "=== TENNIS PLAYER BUILDER ===\n";
    std::cout << "1. Single Player\n";
    std::cout << "2. Two Players\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose mode: ";

    if (!readChoice(mode, 0, 2))
        return 0;

    if (mode == 0)
    {
        return 0;
    }

    if (mode == 1)
    {
        TennisGame game;
        loadPlayers(game);
        game.startGame();
    }
    else if (mode == 2)
    {
        TennisGame player1;
        TennisGame player2;

        loadPlayers(player1);
        loadPlayers(player2);

        if (!startTwoPlayerDraft(player1, player2))
            return 0;

        int rating1 = player1.calculateRating();
        int rating2 = player2.calculateRating();

        std::cout << "\x1b[2J\x1b[H";
        showResultPanels(player1, player2, rating1, rating2);

        if (rating1 > rating2)
        {
            std::cout << "Winner: Player 1\n";
        }
        else if (rating2 > rating1)
        {
            std::cout << "Winner: Player 2\n";
        }
        else
        {
            std::cout << "Draw!\n";
            player1.startTiebreaker(player2);
        }
    }
    else
    {
        std::cout << "Invalid option.\n";
    }

    return 0;
}
