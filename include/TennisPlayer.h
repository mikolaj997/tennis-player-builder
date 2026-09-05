#pragma once

#include <string>
#include "Attribute.h"

class TennisPlayer {
private:
    std::string name;

    std::array<int, attributeCount> ratings;

public:
    TennisPlayer(
        const std::string& name,
        int forehand,
        int backhand,
        int serve,
        int volley,
        int dropShot,
        int stamina,
        int mentalStrength
    );

    std::string getName() const;
    int getRating(Attribute attribute) const;
};
