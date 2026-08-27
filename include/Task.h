#pragma once

#include <string>

struct Task {
    int id;
    std::string name;
    bool completed;

    Task(int id, const std::string& name);
};