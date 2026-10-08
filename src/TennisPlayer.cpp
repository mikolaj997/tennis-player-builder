#include "TennisPlayer.h"

TennisPlayer::TennisPlayer(
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
    int mentalStrength)
    : name(name),
      ratings{
          forehand,
          backhand,
          serve,
          returnRating,
          volley,
          dropShot,
          slice,
          power,
          stamina,
          speed,
          defense,
          mentalStrength}
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
