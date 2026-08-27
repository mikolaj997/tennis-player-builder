#pragma once

#include "Task.h"
#include <vector>

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;

public:
    TaskManager();

    void addTask(const std::string& name);
    void showTasks() const;
    void completeTask(int id);
    void removeTask(int id);
    void searchTask(const std::string& phrase) const;
    void showStatistics() const;
};