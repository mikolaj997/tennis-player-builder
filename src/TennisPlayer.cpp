#include "TennisPlayer.h"

TennisPlayer::TennisPlayer(const std::string& name)
    : name(name) {
}

std::string TennisPlayer::getName() const {
    return name;
}