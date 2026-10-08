#pragma once

#include <array>
#include <cstddef>

enum class Attribute
{
    Forehand,
    Backhand,
    Serve,
    Return,
    Volley,
    DropShot,
    Slice,
    Power,
    Stamina,
    Speed,
    Defense,
    MentalStrength,
    Count
};

inline constexpr std::size_t attributeCount =
    static_cast<std::size_t>(Attribute::Count);

inline constexpr std::array<const char *, attributeCount> attributeNames = {
    "Forehand",
    "Backhand",
    "Serve",
    "Return",
    "Volley",
    "Drop Shot",
    "Slice",
    "Power",
    "Stamina",
    "Speed",
    "Defense",
    "Mental Strength"};

inline const char *attributeName(Attribute attribute)
{
    return attributeNames.at(static_cast<std::size_t>(attribute));
}