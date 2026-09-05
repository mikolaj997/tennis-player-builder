cmake_minimum_required(VERSION 3.16)

project(TennisPlayerBuilder VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tennis-player-builder
    src/main.cpp
    src/TennisPlayer.cpp
    src/TennisGame.cpp
)

target_include_directories(tennis-player-builder PRIVATE include)

include(CTest)
if(BUILD_TESTING)
    add_executable(tennis-game-tests
        tests/TennisGameTests.cpp
        src/TennisPlayer.cpp
        src/TennisGame.cpp
    )
    target_include_directories(tennis-game-tests PRIVATE include)
    add_test(NAME tennis-game-regressions COMMAND tennis-game-tests)
endif()
