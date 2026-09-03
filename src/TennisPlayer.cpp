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
      forehand(forehand),
      backhand(backhand),
      serve(serve),
      volley(volley),
      dropShot(dropShot),
      stamina(stamina),
      mentalStrength(mentalStrength)
{
}

std::string TennisPlayer::getName() const
{
    return name;
}
int TennisPlayer::getRating(const std::string &attribute) const
{
    if (attribute == "forehand")
        return forehand;

    if (attribute == "backhand")
        return backhand;

    if (attribute == "serve")
        return serve;

    if (attribute == "volley")
        return volley;

    if (attribute == "dropShot")
        return dropShot;

    if (attribute == "stamina")
        return stamina;

    if (attribute == "mentalStrength")
        return mentalStrength;

    return 0;
}