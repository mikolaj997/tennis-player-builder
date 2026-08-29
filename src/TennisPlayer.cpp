#include "TennisPlayer.h"

TennisPlayer::TennisPlayer(
    const std::string& name,
    int forehand,
    int backhand,
    int serve,
    int volley,
    int dropShot,
    int stamina,
    int mentalStrength
)
    : name(name),
      forehand(forehand),
      backhand(backhand),
      serve(serve),
      volley(volley),
      dropShot(dropShot),
      stamina(stamina),
      mentalStrength(mentalStrength) {
}

std::string TennisPlayer::getName() const {
    return name;
}