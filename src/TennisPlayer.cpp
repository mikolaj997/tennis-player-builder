#include "TennisPlayer.h"

TennisPlayer::TennisPlayer(
    const std::string &name,
    int forehand,
    int backhand,
    int serve,
    int volley,
    int dropShot,
    int stamina,
    int mentalStrength)
    : name(name),
      ratings{forehand, backhand, serve, volley, dropShot, stamina, mentalStrength}
{
}

std::string TennisPlayer::getName() const
{
    return name;
}
int TennisPlayer::getRating(Attribute attribute) const
{
    return ratings.at(static_cast<std::size_t>(attribute));
}
