#include "TennisGame.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

void require(bool condition)
{
    if (!condition)
        throw std::runtime_error("Regression check failed");
}

int main()
{
    std::ostringstream output;
    auto *oldOutput = std::cout.rdbuf(output.rdbuf());
    std::istringstream input("abc\n8\n1\n1\n2\n3\n4\n5\n6\n7\n");
    auto *oldInput = std::cin.rdbuf(input.rdbuf());

    TennisGame game;
    for (int i = 0; i < 10; ++i)
        game.addPlayer("Original", 70, 71, 72, 73, 74, 75, 76);
    require(game.startGame());
    require(game.calculateRating() == 73);
    require(output.str().find("Attribute already taken") != std::string::npos);
    require(output.str().find("ROUND 8") == std::string::npos);

    // Force vector growth after assigning every attribute.
    for (int i = 0; i < 1000; ++i)
        game.addPlayer("Added", 1, 1, 1, 1, 1, 1, 1);
    require(game.calculateRating() == 73);
    auto copy = game;
    game = TennisGame{};
    require(copy.calculateRating() == 73);

    TennisGame skipped;
    for (int i = 0; i < 10; ++i)
        skipped.addPlayer("Player", 80, 80, 80, 80, 80, 80, 80);
    input.str("0\n0\n0\n0\n1\n2\n3\n4\n5\n6\n7\n");
    std::cin.clear();
    require(skipped.startGame());
    require(skipped.calculateRating() == 80);
    require(output.str().find("No skips left") != std::string::npos);

    // Large rosters allow at most five skips per player in both input modes.
    TennisGame largePool;
    for (int i = 0; i < 31; ++i)
        largePool.addPlayer("Player " + std::to_string(i), 80, 80, 80, 80, 80, 80, 80);
    auto secondPlayer = largePool;
    require(largePool.skipsLeft() == 5);
    require(!largePool.skipRound());
    for (int i = 0; i < 5; ++i)
    {
        require(largePool.prepareRound());
        require(largePool.skipRound());
        require(largePool.skipsLeft() == 4 - i);
    }
    require(secondPlayer.skipsLeft() == 5);
    require(largePool.prepareRound());
    const auto pendingName = largePool.pendingPlayerName();
    require(!largePool.skipRound());
    require(largePool.pendingPlayerName() == pendingName);
    for (std::size_t i = 0; i < attributeCount; ++i)
    {
        require(largePool.prepareRound());
        require(largePool.selectAttribute(static_cast<Attribute>(i)));
        require(largePool.skipsLeft() == 0);
    }
    require(largePool.isComplete());
    input.str("0\n0\n0\n0\n0\n0\n1\n2\n3\n4\n5\n6\n7\n");
    std::cin.clear();
    output.str("");
    require(secondPlayer.startGame());
    require(secondPlayer.skipsLeft() == 0);
    require(output.str().find("No skips left") != std::string::npos);
    require(output.str().find("ROUND 13") == std::string::npos);

    input.str("");
    std::cin.clear();
    TennisGame interrupted;
    interrupted.addPlayer("Player", 1, 2, 3, 4, 5, 6, 7);
    require(!interrupted.startGame());
    std::cin.clear();
    copy.startTiebreaker(copy); // EOF while choosing from the bench.
    require(std::cin.fail());

    std::cin.rdbuf(oldInput);
    std::cin.clear();
    std::cout.rdbuf(oldOutput);
    std::cout << "All regression checks passed.\n";
}
