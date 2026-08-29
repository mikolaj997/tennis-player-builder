#pragma once

#include <string>

class TennisPlayer {
private:
    std::string name;

public:
    TennisPlayer(const std::string& name);

    std::string getName() const;
};