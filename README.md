# Tennis Player Builder

A C++ console game where players build their own tennis player by assigning
attributes to randomly selected professional tennis players.

## About

The game offers two modes:

- **Single Player** – build your own tennis player and see the final rating.
- **Two Players** – two players independently build their tennis players and
  compare their final ratings.

During each round, a random tennis player is displayed. The player can assign
one of the available attributes to that tennis player or skip the player.

Each tennis player has predefined ratings for:

- Forehand
- Backhand
- Serve
- Volley
- Drop Shot
- Stamina
- Mental Strength

The ratings are hidden during the selection process and are revealed only
when the final player is evaluated.

## Features

- Random player selection
- No repeated players within a single draft
- Seven different tennis attributes
- Skip mechanic
- Hidden attribute ratings
- Final player rating
- Single-player mode
- Two-player mode
- Winner determination
- CMake build support
- Makefile build support

## Technologies

- C++17
- CMake
- GNU Make
- MinGW / GCC

## Project Structure

```text
tennis-player-builder/
├── CMakeLists.txt
├── Makefile
├── README.md
├── include/
│   ├── TennisPlayer.h
│   └── TennisGame.h
└── src/
    ├── TennisPlayer.cpp
    ├── TennisGame.cpp
    └── main.cpp
```

## How to Run

### Using CMake

From the project root:

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build 

./build/tennis-player-builder.exe
```

### Using Make
```bash
make run
```