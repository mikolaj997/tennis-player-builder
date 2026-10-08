#pragma once

#include <string>
#include "Attribute.h"

class TennisPlayer
{
private:
    std::string name;

    std::array<int, attributeCount> ratings;

public:
    TennisPlayer(
        const std::string &name,
        int forehand,
        int backhand,
        int serve,
        int returnRating,
        int volley,
        int dropShot,
        int slice,
        int power,
        int stamina,
        int speed,
        int defense,
        int mentalStrength);

    std::string getName() const;
    int getRating(Attribute attribute) const;
};
