#pragma once

#include <iostream>
#include <sstream>
#include <string>

// Read one complete answer; reject trailing text and overflowing integers.
inline bool readChoice(int &choice, int minimum, int maximum)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::istringstream input(line);
        int value;
        if (input >> value)
        {
            input >> std::ws;
            if (input.eof() && value >= minimum && value <= maximum)
            {
                choice = value;
                return true;
            }
        }
        std::cout << "Invalid choice. Enter a number from " << minimum
                  << " to " << maximum << ": ";
    }
    return false;
}
