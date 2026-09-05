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
