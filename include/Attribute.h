#pragma once

#include <array>
#include <cstddef>

enum class Attribute
{
    Forehand,
    Backhand,
    Serve,
    Volley,
    DropShot,
    Stamina,
    MentalStrength,
    Count
};

inline constexpr std::size_t attributeCount = static_cast<std::size_t>(Attribute::Count);
inline constexpr std::array<const char *, attributeCount> attributeNames = {
    "Forehand", "Backhand", "Serve", "Volley", "Drop Shot", "Stamina", "Mental Strength"};

inline const char *attributeName(Attribute attribute)
{
    return attributeNames.at(static_cast<std::size_t>(attribute));
}
