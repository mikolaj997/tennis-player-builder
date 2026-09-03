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

## Screen shots:
### One player mode:
<img width="321" height="974" alt="image" src="https://github.com/user-attachments/assets/ad9ef81f-fcd5-4252-90f2-221cc1e3ed39" />

<img width="387" height="973" alt="image" src="https://github.com/user-attachments/assets/04814ee7-7ce1-4d42-924c-0022e59a6444" />

### Two players mode:
<img width="338" height="972" alt="image" src="https://github.com/user-attachments/assets/819bb0a6-fa4f-4734-ab86-2bda87619011" />

<img width="369" height="968" alt="image" src="https://github.com/user-attachments/assets/59688f6b-3792-4951-b879-99e52b851eff" />

<img width="414" height="915" alt="image" src="https://github.com/user-attachments/assets/4011533c-843b-4ba6-ae0c-67abd7ec7afe" />




