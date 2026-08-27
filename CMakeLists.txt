cmake_minimum_required(VERSION 3.16)

project(TaskManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task-manager
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
)

target_include_directories(task-manager PRIVATE include)