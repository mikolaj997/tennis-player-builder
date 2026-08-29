#pragma once

#include <string>

class TennisPlayer {
private:
    std::string name;

    int forehand;
    int backhand;
    int serve;
    int volley;
    int dropShot;
    int stamina;
    int mentalStrength;

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
};